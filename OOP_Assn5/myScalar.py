import myString
import myMatrix

class myScalar:

	def __init__(self, val):
		# check the input parameter
		if type(val)!=float:
			raise NameError('Initialization Fail')
		# member variable assign
		self.val = val

	def __str__(self): # Make myScalar to string value for scoring
		return str(self.val)

############ do not change the above lines ############

	def __add__(self, op): #+연산자 오버로딩
		if type(op) is myScalar: #scalar + scalar
			return myScalar(self.val+op.val)
		elif type(op) is myMatrix.myMatrix: #scalar + matrix
			return (op + self)
		elif type(op) is myString.myString: #scalar + string
			return myString.myString(str(self.val)+op.val)
		else:
			raise NameError('Not defined')

	def subMatrix(self, op): #scalar - matrix 연산을 수행하는 함수
        	res = myMatrix.myMatrix(op.row, op.col)
        	for i in range(len(op.val)):
                	for j in range(len(op.val[i])):
                        	res.val[i][j] = self.val - op.val[i][j]
        	return res

	def __sub__(self, op):#-연산자 오버로딩
        	if type(op) is myScalar: #scalar - scalar
                	return myScalar(self.val-op.val)
        	elif type(op) is myMatrix.myMatrix: #scalar - matrix
                	return self.subMatrix(op)
        	else:
                	raise NameError('Not defined')

	def __mul__(self, op): #*연산자 오버로딩
                if type(op) is myScalar: #scalar * scalar
                        return myScalar(self.val * op.val)
                elif type(op) is myMatrix.myMatrix: #scalar * matrix
                        return (op * self)
                elif type(op) is myString.myString: #scalar * string
                        if self.val >= 0: #scalar의 값이 0보다 크거나 같을 경우
                                return (op.val * int(self.val)) #string을 val의 정수부분만큼 반복함
                        else: #scalar의 값이 음수인 경우
                                outStr = ""
                                count = len(op.val)
                                i = 0

                                for i in range(0, count) : #string을 거꾸로 outStr에 입력함
                                        outStr += op.val[count - (i+1)]

                                return (outStr * -(int(self.val))) #string을 거꾸로 한 것을 val의 정수부분만큼 반복
                else:
                        raise NameError('Not defined')

	def __truediv__(self, op): #/연산자 오버로딩
                if type(op) is myScalar: #scalar / scalar
                        return myScalar(self.val / op.val)
                else:
                        raise NameError('Not Defined')
