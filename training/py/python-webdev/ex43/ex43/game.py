from random import randint

class Engine(object):
    def __init__(self, scene_map):
        self.scene_map = scene_map
        pass
    
    def play(self):
        current_scene = self.scene_map.opening_scene()
        last_scene = self.scene_map.next_scene('go_home')
        
        while current_scene != last_scene:
            next_scene_name = current_scene.enter()
            current_scene = self.scene_map.next_scene(next_scene_name)
         
        #print out the last scene
        current_scene.enter()
        
class Map(object):
    def __init__(self, start_scene):
        pass
    def next_scene(self, scene_name):
        pass
    def opening_scene(self):
        pass

class Scene(object):
    def enter(self):
        pass

    def review_checklist():
        pass

class ChecklistIsntComplete(Scene):
    def __init__(self):
        self.quips = [
            'The cickens got upset and have escaped.',
            'Baby Zombies have captured the chickens and now ride them around \
            as Chicken Jokeys',
            'The chickens died'
        ]
    def enter(self):
        print 'It looks like you didnt finish all your tasks! ', self.quips[randint(0,2)] 
        exit(1)

class OpenCoop(Scene):
    def __init__(self):
        self.checklist = {
            'Open the Pen':0,
            'Open the Coop':0, 
            'Give Chickens Scratch':0, 
            'Close The Pen':0
        }
        self.actionlist = {
            'Open the Pen':0,
            'Open the Coop':1, 
            'Give Chickens Scratch':2, 
            'Close The Pen':3, 
            'Finish':4
        }
        self.intro = '\nWelcome to the Chicken Coop Game. You\'re neighbors '
        self.intro += 'are leaving for one day and have asked you to take care of '
        self.intro += 'their chickens. It is now time to start. The owners have left '
        self.intro += 'you a checklist of each thing you need to do. Good luck! \n'
        self.intro += '\nIt is Time to open the coop, '

    def enter(self):
        print self.intro

        # Review Check List
        text = 'after reviewing your checklist you see that you need to: \n\n'
        for k in self.checklist.keys(): text += k + ', '
        print text

        # Take Next Action, move on if Finished
        while (self.actionlist['Finish'] is not 'done'):
            self.next_action()
        if 0 in [self.checklist[task] for task in self.checklist]: 
            return 'checklist_isnt_complete'
        else: return 'feeding' 

    def next_action(self):

        print '\nwhat would you like to do next?'
        for task in self.actionlist: 
            if self.actionlist[task] is not 'done': 
                print '%s, ' % task

        action = raw_input("> ")
        if action in self.checklist.keys():
            print '\ngreat!' 
        else:
            print '\nsure thing, I guess.\n'
        self.actionlist[action] = 'done' 
        self.checklist[action] = 'done'

class Feeding(Scene):
    def enter(self):
        print "Time to feed the chickens"
        return "eggs"
    def review_checklist():
        pass

class Eggs(Scene):
    def enter(self):
        print "Time to collect Eggs"
        return "clean_coop"
    def review_checklist():
        pass

class CleanCoop(Scene):
    def enter(self):
        print "Time to clean the coop"
        return "close_coop"
    def review_checklist():
        pass

class CloseCoop(Scene):
    def enter(self):
        print "Time to close the coop" 
        return "go_home"
    def review_checklist():
        pass
    
class GoHome(Scene):
    def enter(self):
         print "You've done a good job, now you can go home!"
         return "go_home"

class Map(object):

    scenes = {
        'open_coop' : OpenCoop(),
        'feeding' : Feeding(),
        'eggs' : Eggs(),
        'clean_coop' : CleanCoop(),
        'close_coop' : CloseCoop(),
        'checklist_isnt_complete' : ChecklistIsntComplete(),
        'go_home' : GoHome()
        }

    def __init__(self, start_scene):
        self.start_scene = start_scene

    def next_scene(self, scene_name):
        val = Map.scenes.get(scene_name)
        return val

    def opening_scene(self):
        return self.next_scene(self.start_scene) 

a_map = Map('open_coop')
a_game = Engine(a_map)
a_game.play()

"""
#Checklist, tasks: open_coop, close_coop, open_pen, close_pen, collect_eggs, clean_coop
Scene
    print intro
    review checklist
    while not done
      prompt for action
      update check list    
    if incomplete in checklist: return CheckListIsntComplete
    else return next scene
"""
