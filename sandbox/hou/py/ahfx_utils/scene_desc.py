""" scene description utilities """

# library imports
import os
import json

# hou imports
import hou

# util imports
import parm
#import hda_utils

def save_scene_desc_to_file(element_dict, scene_desc_file):
    """ save scene desc to file """

    # format element data into scene_desc json

    # save scene desc file

def load_scene_desc_from_file(scene_desc_file):
    """ load scene desc file """

    # check if file exists, if not throw error

    scene_desc_dict = dict()

    # open file
    with open(scene_desc_file) as scene_desc_json:
        scene_desc_dict = json.load(scene_desc_json)

    # get json data
    element_type = scene_desc_dict['entry_0']['element']['type']
    element_path = scene_desc_dict['entry_0']['element']['path']
    node_type = scene_desc_dict['entry_0']['element']['node_type']
    parent_node_path = scene_desc_dict['entry_0']['parent_node']

    parm_json_file = scene_desc_dict['entry_0']['parms']
    anim_clip_file = scene_desc_dict['entry_0']['anim']

    # resolve relative paths in file names
    cwd = os.getcwd()
    os.chdir(os.path.dirname(scene_desc_file))
    parm_json_file = os.path.abspath(parm_json_file)
    parm_json_file = os.path.abspath(parm_json_file)
    os.chdir(cwd)

    # create node(s)
    node = hou.node(parent_node_path).createNode(node_type)

    # load parm and anim data
    parm.load_parm_json(node, parm_json_file)
    parm.load_node_clip(node, anim_clip_file)