# Reading Python Internals
source - [PyCon - Python Internals Talk](https://www.youtube.com/watch?v=s5_5XmmwMx8)
more reading: [Exploring Python Code Objects](https://late.am/post/2012/03/26/exploring-python-code-objects.html)

ipython %timeit will figure out a reasonable amount of iterations to run

## dis.disassemble (dis.dis)
dis.disassemble (dis.dis in python 3) will show you the BYTE code being executed (when python compiles your code, it is compiling it into byte code and places it in .pyc files)

eg:

	>>> import dis
	>>> what = 'World'
	>>> def say_hello():
	...     msg = 'Hello {}'.format(what)
	...     print(msg)
	...
	
	>>> dis.dis(say_hello.__code__)

dis.dis output (python virutal machine instructions being executed):

	  2           0 LOAD_CONST               1 ('Hello {}')
	              2 LOAD_ATTR                0 (format)
	              4 LOAD_GLOBAL              1 (what)
	              6 CALL_FUNCTION            1
	              8 STORE_FAST               0 (msg)
	
	  3          10 LOAD_GLOBAL              2 (print)
	             12 LOAD_FAST                0 (msg)
	             14 CALL_FUNCTION            1
	             16 POP_TOP
	             18 LOAD_CONST               0 (None)
	             20 RETURN_VALUE
