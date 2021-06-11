import sys
import inspect
import weakref

import Application
import GL
import component
import node

sys.stdout.write('--------------------------------------------------------------------------------------------------\n')


def runLoop(n):
    pass#print('PYTHON> def runLoop()', n)

#status = GL.ActiveTexture('ls -l')
status = Application.set_runLoop(runLoop)

status = runLoop(456)
#status = Application.runLoop(789)

#d = {'a':0, 'b':1, 'c':2}
#component.parrot(voltage=10, state='s', action='a', type='t')#, object=d)

#print('path: ', Application.path)
#print("Application.root - refcount: ", sys.getrefcount(Application.root)-1)

root = Application.root
print("root - refcount: ", sys.getrefcount(root))


#new----------------------------------------------------------------
#array = []
#tuple = ()


#tex0 = GL.import(name='unity_poster.tga')
#tr = GL.texture_renderer(texture = tex0)

#tr.draw(pos=(100,100), color=0xffffffff, alpha=1.0)
class node_frame_rect(node.node):
    def __init__(self, name: str, owner:object) -> None:
        node.node.__init__(self, name, owner)

    def draw(self):
        #print('hjfsdhk')
        node.node.draw(self)
        pass

n4 = node_frame_rect('node_frame_rect', root)
root.add(n4)
n4.draw()
#n4.owner = n3
n4.draw()

root.dump()


"""
from typing import TypeVar, Generic
from logging import Logger

T = TypeVar('T')

class LoggedVar(Generic[T]):
    def __init__(self, value: T, name: str) -> None:
        self.name = name
        self.value = value

    def set(self, new: T) -> None:
        self.log('Set ' + repr(self.value))
        self.value = new

    def get(self) -> T:
        self.log('Get ' + repr(self.value))
        return self.value

    def log(self, message: str) -> None:
        print('name: ', self.name, message)


#log = LoggedVar[int]("123", "str")        
#log.set(3)
"""

sys.stdout.write('--------------------------------------------------------------------------------------------------\n')
