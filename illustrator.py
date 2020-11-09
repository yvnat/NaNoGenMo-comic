# illustrator.py
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# illustrates a frame based on a description

import pygame
import os
import sys

########################################################################
# temporary implementation of C++ classes
class CharacterAction:
    def __init__(self):
        self.character = None;
        self.pose = "stand";
        self.dialogue = "hello";

class Frame:
    def __init__(self, number, page_number):
        self.number = number
        self.page_number = page_number
        self.actions = [CharacterAction(), CharacterAction()];

class PageSketch:
    def __init__(self):
        self.number = 1
        self.frames = [Frame(1, self.number), Frame(2, self.number)];
########################################################################

pygame.init();
FRAME_X = 660
FRAME_Y = 660
screen = pygame.display.set_mode((FRAME_X, FRAME_Y));
font = pygame.font.SysFont(None, 24)

########################################################################

dir = os.path.dirname(os.path.realpath(sys.argv[0]))+"/";

def drawFrame(frame):
    FRAME_X = 660
    FRAME_Y = 660
    screen = pygame.display.set_mode((FRAME_X, FRAME_Y));
    drawScenery(frame);
    drawActions(frame);
    saveAsPNG(frame);

def drawScenery(frame):
    screen.fill((77,195,255));
    pygame.draw.rect(screen, (100,200,0), (0, FRAME_Y/2, FRAME_X, FRAME_Y/2));

def drawActions(frame):
    numCharacters = len(frame.actions)
    for i in range(len(frame.actions)):
        pose = frame.actions[i].pose
        os.system("python3 "+dir+"characters/armature.py "+pose);
        
        img = pygame.image.load(dir+"characters/output/"+pose+".png");
        scale = int(min(FRAME_X, FRAME_Y)/numCharacters);
        img = pygame.transform.scale(img, (scale, scale))
        img.set_colorkey((255, 0, 255));
        
        x = i*(FRAME_X/(numCharacters));
        screen.blit(img, (x, FRAME_Y/4));

        text = font.render(frame.actions[i].dialogue, True, (0,0,0))
        screen.blit(text, (x+(FRAME_X/(4*numCharacters)), 20*i+40))

def saveAsPNG(frame):
    output_dir = dir+"output/"+str(frame.page_number)
    if not os.path.isdir(output_dir):
        os.mkdir(output_dir);
    pygame.image.save(screen, output_dir+"/"+str(frame.number)+".png")

def drawPage(page):
    for frame in page.frames:
        print("#######MAKING "+str(frame.page_number)+":"+str(frame.number));
        drawFrame(frame);

p = PageSketch()
drawPage(p);

pygame.quit()