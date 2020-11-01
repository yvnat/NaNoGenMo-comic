# armature.py
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# creates a posable character from various limb parts

"""
TODO

finish integrating json with save

make body.load_pose_from_json() function that loads pose from json

slightly change pose loading function to correctly handle having more children than are described in the json

do load pose from file

give poses names

"""

################################################################################
from math import sin, cos, pi
import math
import pygame
import time
import json
###############################################################################
SCREEN_X = 660
SCREEN_Y = 660

pygame.init()
screen = pygame.display.set_mode((SCREEN_X, SCREEN_Y))
###############################################################################

class Graphic:
    """An image and its associated pivot point"""
    def __init__(self, src, pivot, recolour=None):
        """
        params:
            src: string, path to the image
            pivot: (x,y) the pivot point, from top left corner
            recolour: None or (r,g,b). If recolour is given, replaces all white 
                     (255,255,255) with recolour
        """
        self.src = src;
        self.recolour = recolour;
        self.pivot = pivot;
        self.image = pygame.image.load(src);
        if recolour:
            px_array = pygame.PixelArray(self.image);
            px_array.replace((255, 255, 255), recolour);
    def get_copy(self):
        """Returns a copy of itself"""
        return Graphic(self.src, self.pivot)

def mirror(graphic):
    """Takes a graphic and returns a copy mirrored across the vertical"""
    mir_pivot = (graphic.image.get_width()-graphic.pivot[0],    #x is mirrored
                 graphic.pivot[1]);                             #y is not
    mir_image = pygame.transform.flip(graphic.image, True, False)
    mir_graphic = graphic.get_copy();
    mir_graphic.pivot = mir_pivot;
    mir_graphic.image = mir_image;
    return mir_graphic;

def draw_crosshairs(x, y, colour=(255,0,255)):
    """Draws a (by default magenta) crosshairs at x,y. Useful for debugging."""
    pygame.draw.line(screen, colour, (0, int(y)), (SCREEN_X, int(y)));
    pygame.draw.line(screen, colour, (int(x), 0), (int(x), SCREEN_Y));

def draw_image(graphic, angle, x, y):
    """
    Draws an image, rotated around and centered on its defined pivot point
    params:
        graphic: a Graphic instance
        angle: float, counterclockwise rotation in degrees
        x, y: the coordinates at which the pivot should be drawn on the canvas
    """
    theta = angle*0.01745329;   #angle in radians
    img = graphic.image;
    pivot = graphic.pivot;
    
    #rotate the image
    rot_img = pygame.transform.rotate(img, angle)

    #establish its original center, and vector from center to pivot
    center = (int(img.get_width()/2), int(img.get_height()/2))
    pivot_vector = (pivot[0]-center[0], pivot[1]-center[1]);

    #establish the center of the rotated image
    rot_center = (int(rot_img.get_width()/2), int(rot_img.get_height()/2))
    #rotate pivot_vector
    rot_vector = (pivot_vector[0]*cos(-theta) - pivot_vector[1]*sin(-theta),
                  pivot_vector[0]*sin(-theta) + pivot_vector[1]*cos(-theta))

    screen.blit(rot_img, (int(x-rot_center[0]-rot_vector[0]),
                          int(y-rot_center[1]-rot_vector[1])));

################################################################################

class Limb:
    def __init__(self, graphic, mount_point, 
                 clothes_graphic = None, priority=False, 
                 absolute_coords=(0,0), angle=0):
        """
        params:
            graphic: an instance of Graphic.
            mount_point: (x,y) where this is mounted on the parent 
                        (in parent's coordinates).
            clothes_graphic: instance of Graphic or none; optional clothes 
                            overlay. Clothes are drawn after all bare limbs.
            priority: whether this is drawn above everything else.
            absolute_coords: the absolute location of this limb. Automatically 
                            changed.
            angle: the angle of this limb relative to its parent, in degrees.
        """
        self.graphic = graphic;
        self.clothes_graphic = clothes_graphic;
        self.own_angle = angle;     #relative angle to parent, in degrees
        self.priority = priority;   #whether this limb has drawing priority

        #only meaningfully initialized for root
        self.absolute_x, self.absolute_y = absolute_coords;
        self.parent_angle = 0;  #set by update_children_coordinates()

        #where this is mounted on the parent (in parent's coordinates).
        self.mount_point = mount_point;
        #limb begins with no children
        self.children = [];

    # ------------------ CONTROL ------------------ #
    def draw(self):
        """Draws this limb"""
        draw_image(self.graphic, self.get_angle(), 
                   self.absolute_x, self.absolute_y);    
    def draw_clothes(self):
        """Draws the clothes overlay of this limb."""
        if (self.clothes_graphic is None):
            return;
        draw_image(self.clothes_graphic, self.get_angle(), 
                   self.absolute_x, self.absolute_y);

    def add_child(self, child):
        """Adds a child limb"""
        self.children.append(child);

    def update_children_coordinates(self):
        """Recursively updates the coordinates of all children"""
        for child in self.children:
            #set the absolute coordinates of the child
            absolute = self._absolute_coordinates(child.mount_point);
            child.absolute_x, child.absolute_y = absolute;
            #update the angle of the child
            child.parent_angle = self.get_angle();
            #run this function recursively for the child
            child.update_children_coordinates();
    
    def establish_drawing_order(self, order, priority):
        """Recursively establish the drawing order of limbs"""
        for child in self.children:
            childs_output = child.establish_drawing_order(order, priority)
            order = childs_output[0];
            priority = childs_output[1];
        if self.priority:
            priority.append(self);
        else:
            order.append(self);
        return (order, priority);

    def rotate(self, angle):
        """
        Sets the new relative (to the parent) rotation of the limb 
        (in degrees; counterclockwise)
        """
        self.own_angle = angle%360;
        self.update_children_coordinates();
    def get_angle(self):
        """Return this Limb's absolute angle in degrees"""
        return self.own_angle + self.parent_angle;
    def get_theta(self):
        """Return this Limb's absolute angle in radians"""
        return self.get_angle()*0.0174532925199;

    def save_pose(self):
        """Recursively returns this limb and its childrens' poses"""
        s_angle = self.own_angle;
        s_priority = self.priority;
        s_children = []
        for child in self.children:
            s_children.append(child.save_pose());
        return (s_angle, s_priority, s_children);

    def load_pose(self, pose):
        """Recursively load a pose as outputted by save_pose"""
        self.own_angle = pose[0];
        self.priority = pose[1];
        for i in range(len(self.children)):
            self.children[i].load_pose(pose[2][i]);

    # ------------------ PRIVATE ------------------ #
    def _to_absolute_axes(self, coords):
        """
        params:
            (x,y) along rotated relative axes (where 0,0 is the pivot point)
        return:
            (x,y) of the same points along the unrotated axes (0,0 remains same)
        """
        x, y = coords;
        theta = self.get_theta();
        return (x*cos(-theta) - y*sin(-theta),
                x*sin(-theta) + y*cos(-theta));
    
    def _absolute_coordinates(self, coords):
        """
        Returns the absolute coordinates on the canvas of point (x,y) on limb.
        """
        x, y = self._to_absolute_axes(coords)
        return (self.absolute_x + x, self.absolute_y + y);

################################################################################

class Body:
    def __init__(self, body, coordinates):
        self.body = body;
        self.x, self.y = coordinates;

        #create drawing order
        drawing_order_output = self.body.establish_drawing_order([], []);
        self.drawing_order = drawing_order_output[0] + drawing_order_output[1];

        self.update();
    
    def draw(self):
        for limb in self.drawing_order:
            limb.draw();
        for limb in self.drawing_order:
            limb.draw_clothes();
    
    def update(self):
        #update the drawing order
        drawing_order_output = self.body.establish_drawing_order([], []);
        self.drawing_order = drawing_order_output[0] + drawing_order_output[1];

        self.body.absolute_x = self.x;
        self.body.absolute_y = self.y
        self.body.update_children_coordinates();

    def save_pose(self, filepath):
        pose = self.body.save_pose();
        pose_string = json.dumps(pose)
        file = open("poses/"+filepath+".json", "w");
        file.write(pose_string);
        file.close();
        print("Saved ","poses/"+filepath+".json")

    def load_pose(self, filepath):
        try:
            file = open("poses/"+filepath+".json", "r");
            json_string = file.read();
            file.close();
        except FileNotFoundError:
            print("No such file", "poses/"+filepath+".json");
            return;
        pose = json.loads(json_string);
        self.body.load_pose(pose);


################################################################################
################################################################################
################################################################################

def editor():
    """A quick and dirty graphical pose editor"""
    # -------- graphics -------- #
    # taken from 
    # https://commons.wikimedia.org/wiki/
    #   File:Greek_soldiers_of_Greco%E2%80%93Persian_Wars.png
    torso_graphic = Graphic("graphics/torso.png", (52, 174));
    arm_top_graphic = Graphic("graphics/arm_top.png", (19, 30));
    arm_bottom_graphic = Graphic("graphics/arm_bottom.png", (7, 22));
    hand_graphic = Graphic("graphics/hand.png", (5, 16));
    leg_top_graphic = Graphic("graphics/leg_top.png", (8, 32));
    leg_bottom_graphic = Graphic("graphics/leg_bottom.png", (8, 36));
    foot_graphic = Graphic("graphics/foot.png", (2, 60));
    head_graphic = Graphic("graphics/head.png", (74, 142));

    # -------- limbs -------- #

    head = Limb(head_graphic, (-3, -140), None, True);
    torso = Limb(torso_graphic, None, None, False);

    l_arm_top = Limb(arm_top_graphic, (45, -104), None, False, (0,0), -70);
    l_arm_bottom = Limb(arm_bottom_graphic, (90, 0));
    l_hand = Limb(hand_graphic, (76, -2));

    l_leg_top = Limb(leg_top_graphic, (30, 70), None, False, (0,0), -90);
    l_leg_bottom = Limb(leg_bottom_graphic, (84, 3));
    l_foot = Limb(foot_graphic, (125, -8));

    r_arm_top = Limb(mirror(arm_top_graphic), (-39, -104), None, False, (0,0), 70);
    r_arm_bottom = Limb(mirror(arm_bottom_graphic), (-90, 0));
    r_hand = Limb(mirror(hand_graphic), (-76, -2));

    r_leg_top = Limb(leg_top_graphic, (-20, 70), None, False, (0,0), -90);
    r_leg_bottom = Limb(leg_bottom_graphic, (84, 3));
    r_foot = Limb(foot_graphic, (125, -8));

    # -------- assembly -------- #

    torso.add_child(head);

    torso.add_child(l_arm_top);
    l_arm_top.add_child(l_arm_bottom);
    l_arm_bottom.add_child(l_hand);

    torso.add_child(r_arm_top);
    r_arm_top.add_child(r_arm_bottom);
    r_arm_bottom.add_child(r_hand);

    torso.add_child(l_leg_top);
    l_leg_top.add_child(l_leg_bottom);
    l_leg_bottom.add_child(l_foot);

    torso.add_child(r_leg_top);
    r_leg_top.add_child(r_leg_bottom);
    r_leg_bottom.add_child(r_foot);

    body = Body(torso, (330, 330));

    # -------- poser -------- #

    step = 0;
    SPEED = 1
    current_limb = body.body;
    target = None

    while 1:
        switch = False;
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    step = SPEED;
                if event.key == pygame.K_RIGHT:
                    step = -SPEED;
                if event.key == pygame.K_UP:
                    if target is None:
                        target = 0;
                    target += 1;
                if event.key == pygame.K_DOWN:
                    if target is None:
                        target = 0;
                    target -= 1;
                if event.key == pygame.K_ESCAPE:
                    target = None;
                if event.key == pygame.K_SPACE:
                    if not (target is None):
                        switch = True
                if event.key == pygame.K_RETURN:
                    current_limb = body.body;
                if event.key == pygame.K_s:
                    current_limb.rotate(int(input("Relative angle, in deg: ")))
                if event.key == pygame.K_t:
                    print("Rotation increment (currently", SPEED, "): ", end="")
                    SPEED = int(input());
                if event.key == pygame.K_u:
                    current_limb.priority = True;
                if event.key == pygame.K_i:
                    current_limb.priority = False;
                if event.key == pygame.K_e:
                    body.save_pose(input("Save pose as: "));
                if event.key == pygame.K_l:
                    body.load_pose(input("Load pose from file: "));
                if event.key == pygame.K_q:
                    return
                if event.key == pygame.K_h:
                    print(
                    """
                    left/right:        rotate
                    s:                 set angle
                    t:                 set step size

                    up/down:           select children
                    esc:               cancel selection
                    space:             go to child
                    enter:             return to root limb

                    h:                 print this

                    u:                 set limb as priority rendering
                    i:                 unset limb as priority rendering

                    e:                 export pose as string
                    l:                 load pose from string
                    q:                 quit
                    """)
            if event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT:
                    step = 0;
                if event.key == pygame.K_RIGHT:
                    step = 0;
            if event.type == pygame.QUIT:
                return

        if switch:
            current_limb = current_limb.children[target]
            step = 0;
            target = None;
            switch = False

        if not (target is None):
            if len(current_limb.children) == 0:
                target = None;
            else:
                target = target % len(current_limb.children);

        if step:
            current_limb.rotate(current_limb.own_angle+step);

        #draw
        screen.fill((128, 80, 128));
        body.update();
        body.draw();
        
        draw_crosshairs(current_limb.absolute_x, current_limb.absolute_y);
        if not (target is None):
            draw_crosshairs(current_limb.children[target].absolute_x, current_limb.children[target].absolute_y, (0, 255, 0));
        
        pygame.display.flip();
        time.sleep(0.01)

editor();

################################################################################
################################################################################
################################################################################
pygame.quit()
################################################################################