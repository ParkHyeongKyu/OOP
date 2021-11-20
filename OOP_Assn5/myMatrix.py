import myScalar
import myString

class myMatrix:

	# for initialize empty matrix
	def __initEmpty(self, row, col):
		if row <=0 or col <= 0:
			raise NameError('Initialization Fail')
		self.row = row
		self.col = col
		self.val = [([float()] * col) for i in range(row)]

	def __init__(self, row, col, val=[]):
		# for empty matrix
		if not val:
			self.__initEmpty(row,col)
			return
		# check the input parameter
		if type(val)!=list or not all(isinstance(v,float) for v in val) or len(val)!=row*col or row <=0 or col <= 0:
			raise NameError('Initialization Fail')
		# member variable assign
		self.row = row
		self.col = col
		self.val = []
		for i in range(row):
			self.val.append([])
			for j in range(col):
				self.val[i].append(val[col*i+j])

	def __str__(self): # Make myMatrix to string value for scoring
		return str(self.val)

############ DO NOT change the above lines ############

	def addScalar(self,op): #matrix + scalar 연산을 수행해주는 함수
		res = myMatrix(self.row,self.col)
		for i in range(len(self.val)):
			for j in range(len(self.val[i])):
				res.val[i][j] = self.val[i][j] + op.val
		return res

	def addMatrix(self, op): #matrix + matrix 연산을 수행해주는 함수
                if (self.row != op.row) or (self.col != op.col): #행렬 덧셈 예외처리
                        raise NameError('Dimension mismatch')
                res = myMatrix(self.row, self.col)
                for i in range(len(self.val)):
                        for j in range(len(self.val[i])):
                                res.val[i][j] = self.val[i][j] + op.val[i][j]
                return res
                
	def __add__(self, op): #+연산자 오버로딩
		if type(op) is myScalar.myScalar: #matrix + scalar
			return self.addScalar(op)
		elif type(op) is myMatrix: #matrix + matrix
                        return self.addMatrix(op)
		else:
			raise NameError('Not defined')

	def subScalar(self, op): #matrix - scalar 연산을 수행해주는 함수
                res = myMatrix(self.row, self.col)
                for i in range(len(self.val)):
                        for j in range(len(self.val[i])):
                                       res.val[i][j] = self.val[i][j] - op.val
                return res

	def subMatrix(self, op): #matrix - matrix 연산을 수행해주는 함수
                if (self.row != op.row) or (self.col != op.col): #행렬 뺄셈 예외처리
                        raise NameError('Dimension mismatch')
                res = myMatrix(self.row, self.col)
                for i in range(len(self.val)):
                        for j in range(len(self.val[i])):
                                res.val[i][j] = self.val[i][j] - op.val[i][j]
                return res 

	def __sub__(self, op): #-연산자 오버로딩
                if type(op) is myScalar.myScalar: #matrix - scalar
                        return self.subScalar(op)
                elif type(op) is myMatrix: #matrix - matrix
                        return self.subMatrix(op)
                else:
                        raise NameError('Not defined')


	def mulScalar(self, op): #matrix * scalar 연산을 수행해주는 함수
                res = myMatrix(self.row, self.col)
                for i in range(len(self.val)):
                        for j in range(len(self.val[i])):
                                       res.val[i][j] = self.val[i][j] * op.val
                return res

	def mulMatrix(self, op): #matrix * matrix 연산을 수행해주는 함수
                if self.col != op.row: #행렬 곱셈 예외처리
                        raise NameError('Dimension mismatch')
                res = myMatrix(self.row, op.col)
                for i in range(0, self.row): #res 원소 0으로 초기화
                        for j in range(0, op.col):
                                res.val[i][j] = 0
                                       
                for i in range(0, self.row):
                        for j in range(0, op.col):
                                for k in range(0, self.col):
                                       res.val[i][j] += self.val[i][k] * op.val[k][j]
                return res
                                       
	def __mul__(self, op): #*연산자 오버로딩
                if type(op) is myScalar.myScalar: #matrix * scalar
                        return self.mulScalar(op)
                elif type(op) is myMatrix: #matrix * matrix
                        return self.mulMatrix(op)
                else:
                        raise NameError('Not defined')
                                               
	def divScalar(self, op): #matrix / scalar 연산을 수행해주는 함수
                res = myMatrix(self.row, self.col)
                for i in range(len(self.val)):
                        for j in range(len(self.val[i])):
                                res.val[i][j] = self.val[i][j] / op.val
                return res
                                       
	def __truediv__(self, op): #/연산자 오버로딩
                if type(op) is myScalar.myScalar: #matrix / scalar
                        return self.divScalar(op)
                else:
                        raise NameError('Not defined')
                                       
