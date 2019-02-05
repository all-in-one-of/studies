""" parm utils """

# Lib Imports
import os
import json

# utils imports
import os_utils

def save_node_clip(node, clip_file, start=1, end=240, sample_rate=24):
    """ save clip """

    os_utils.create_dir(clip_file)

    node.saveParmClip(clip_file, start=start, end=end, sample_rate=sample_rate, scoped_only=False)

def load_node_clip(node, clip_file, start=1, sample_rate=24):
    """ load clip """

    node.loadParmClip(clip_file, sample_rate=sample_rate, start=start)

def get_parm_dict(node):
    """ get a mapping of parm names to parm values """

    parm_dict = dict()

    for parm in node.parms():
        parm_dict[parm.name()] = parm.eval()

    return parm_dict

def save_parm_json(node, json_file_path):
    """ save node parm dict to json file """

    parm_dict = get_parm_dict(node)

    os_utils.create_dir(json_file_path)

    with open(json_file_path, 'w') as json_file:
        json_file.write(json.dumps(parm_dict))

def load_parm_json(node, json_file_path):
    """ laod dict to node from json file """

    parm_dict = dict()

    with open(json_file_path) as json_file:
        parm_dict = json.load(json_file)

    node.setParms(parm_dict)
