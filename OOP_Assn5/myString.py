import myScalar
import myMatrix

class myString:

	def __init__(self, val):
		# check the input parameter
		if type(val) != str:
			raise NameError('Initialization Fail')
		# member variable assign
		self.val = val
		
	def __str__(self): # Make myString to string value for scoring
		return self.val

############ do not change the above lines ############

	def __add__(self, op): #+연산자 오버로딩
                if type(op) is myScalar.myScalar: #string + scalar
                        return (op + self)
                elif type(op) is myString: #string + string
                        return (self.val + op.val)
                else:
                        raise NameError('Not defined')

	def __mul__(self, op): #*연산자 오버로딩
                if type(op) is myScalar.myScalar: #string * scalar
                        return (op * self)
                else:
                        raise NameError('Not defined')
