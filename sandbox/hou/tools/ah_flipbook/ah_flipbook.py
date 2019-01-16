"""
Write out current view to hipfilepath/../images/hipfilename
"""

import os

import hou
import toolutils

def make_dir(path):
    if not os.path.exists(path):
        os.makedirs(path) 
    return os.path.exists(path)

def viewname():
    viewer = toolutils.sceneViewer()
    viewname = {
        'desktop' : viewer.pane().desktop().name(),
        'pane' : viewer.name(),
        'type' :'world',
        'viewport': viewer.curViewport().name()
    }
    return '{desktop}.{pane}.{type}.{viewport}'.format(**viewname)


def viewwrite(options='', outpath='ip'):
    current_view = viewname()
    cmd = 'viewwrite {0} {1} {2}'.format(options, current_view, outpath)
    hou.hscript(cmd)

#CONFIG FUNCTIONS
def get_lutfile():
    """ Return the default file lut """
    pass

def get_outpath():
    pathargs = {
        'projectdir': hipfilepath(),
        'assetname': hipfilename(),
        'frame': "'$F4'",
        'ext': 'exr'
    }
    
    path = '//{projectdir}/../images/{assetname}'.format(**pathargs)
    if make_dir(path): return '//{projectdir}/../images/{assetname}/{assetname}.{frame}.{ext}'.format(**pathargs)
    else: return ''

def get_framerange():
    return hou.playbar.timelineRange()

#UNIT FUNCTIONS
def stripslashes(s):
    while s.startswith('/'): 
        s = s[1:]
        if s.endswith('/'): s = s[:-1]
    
    while s.endswith('/'): 
        s = s[:-1]    
    return s

def hipfilepath():
    fullpath = hou.hipFile.path()
    basename = hou.hipFile.basename()
    path = fullpath.strip(basename)
    return stripslashes(path)

def hipfilename():
    return hou.hipFile.basename().split('.hip')[0]

def flipbook():
    """ write out flipbook with hscript viewwrite  """

    lutfile = get_lutfile()
    outpath = get_outpath()
    framerange = get_framerange()
    options = '-q 4 -f {0} {1} -c'.format(*framerange)

    print 'ah_flipbook: ', lutfile
    print 'ah_flipbook: ', outpath
    print 'ah_flipbook: ', options
    if outpath: 
       if not hou.ui.displayMessage('Attempting To Capture Frames: {0} to {1} \nImages will go to $HIP/../images/ \nContinue?'.format(framerange[0], framerange[1]), buttons=('Yes', 'No',)):
            viewwrite(options, outpath)
    print 'ah_flipbook: Done'
