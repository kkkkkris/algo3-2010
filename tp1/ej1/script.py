import random

def generarPeor():
	n = 1048576  
	res = []
	for x in range(40):
		n *= 2
		b = random.randint(2, 10000)
		res.append((b, n-1))
	return res

def generarString(res):
	r = [ str(x[0]) + ' ' + str(x[1]) for x in res]
	r = '\n'.join(r)
	r += '\n-1 -1'
	return r

def generarMejor():
	n = 1048576
        res = []
        for x in range(40):
                n *= 2
                b = random.randint(2, 10000)
                res.append((b, n))
        return res


res = generarMejor()
salida = generarString(res)
archivo = file('generarAlgunCaso.in', 'w')
archivo.write(salida)
archivo.close()

		
