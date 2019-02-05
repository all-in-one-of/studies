# TDD With Python

### Write Failing Tests -> Write Code to pass Tests -> Re-factor -> Repeat

## unittest

### project structure
	py/
		module/
			__init__.py
		tests/
			__init__.py
			module_to_test.py	

### tests/module_to_test.py

	import unittest
	
	import module_to_test
	
	class TestClass(unittest.TestCase):
	    """ Test Class """
	
	    def test_method1_to_test(self):
	        """ test module_to_test.method1_to_test """
	        self.assertEqual(module_to_test.method1_to_test(args), desired_result)
	
	    def test_method2_to_test(self):
	        """ test module_to_test.method2_to_test """
	        self.assertEqual(module_to_test.method2_to_test(args), desired_result)

	if __name__ == '__main__':
	    unittest.main()

running tests from the command line
	
	> python -m unittest tests.module_to_test

## coverage
	> coverage run -m unittest tests.module_to_test
	> coverage report