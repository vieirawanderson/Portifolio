

def main():
	while True:
		waves()


Class HookesLaw:
	def init(self, mesh):
		_mesh = mesh
	def waves():
		for each vertex in mesh:
			vextexOldPosition = vertexNewPosition //list form
		
		for each vertex in springs:
			caculateForce(vertex)		

	def calculateForce(vertex):
		acceleration = -(k*x) - (damperFactor * velocity)
		
		for each neighbor in vertex.Neighborhood:
			forceNeighbor = -k * (deltaX(vertex, neighbor)) * getSinBetween(vertex, neighbor);
			acceleration += forceNeighbor
		
		vertexNewPosition = vextexOldPosition + velocity
		velocity += a
		
	def deltaX(vertex, neighbor): 
		x0 = inicialSize(vertex.xz, neighbor.xz) // create inside GFXMath
		x1 = distance(vertex, neighbor)	
		return x1 - x0
		
		
	def getSinBetween(vertex, neighbor):
		deltaY = neighbor.pos.y - vertex.pos.y
		x1 = distance(neighbor, vertex)
		return deltaY / x1
		
	