# deserializer.py
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# deserializes and loads into python PageSketch and related C++ classes

import json
import os
import sys

################################################################################
# The python classes
################################################################################

class PageSketch:
    def __init__(self, array):
        self.frames = [];
        for i in array:
            self.frames.append(Frame(i));

class Frame:
    def __init__(self, array):
        self.sizeX = array[0];
        self.sizeY = array[1];
        self.background = FrameBackground(array[3]);
        self.actions = [];
        for i in array[2]:
            self.actions.append(CharacterAction(i));

class FrameBackground:
    def __init__(self, array):
        self.skyColour = array[0];
        self.groundColour = array[1];
        self.horizonHeight = array[2];

class CharacterAction:
    def __init__(self, array):
        self.pose = array[0];
        self.dialogue = array[1];
        self.position = CharacterActionPosition(array[2]);
        self.appearance = CharacterAppearance(array[3]);

class CharacterActionPosition:
    def __init__(self, array):
        self.positionX = array[0];
        self.positionY = array[1];
        self.size = array[2];
        self.direction = array[3];

class CharacterAppearance:
    def __init__(self, array):
        self.isArmed = array[0];
        self.colour = array[1];

################################################################################
# deserialization functions
################################################################################

def deserialize_sketch_string(sketch):
    """
    Deserializes a single page sketch from string
    """
    array = json.loads(sketch)
    return PageSketch(array);

def deserialize_sketches_file(path):
    """
    Returns an array of all serialized page sketches in a file
    """
    dir = os.path.dirname(os.path.realpath(sys.argv[0]))+"/";
    try:
        file = open(dir+path, "r");
        loaded_string = file.read();
        file.close();
    except FileNotFoundError:
        print("No such file", dir+path);
        return;
    sketches = []
    serialized_sketches = loaded_string.strip().splitlines();
    for i in serialized_sketches:
        sketches.append(deserialize_sketch_string(i));
    return sketches;