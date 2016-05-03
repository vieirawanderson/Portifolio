1)


if n > width && n < (height-1) * width && (n + 1)%4 != 0 && n%4 != 0: // vertex inside
	neighbours = [mesh.vertex[n - w], mesh.vertex[n - w + 1], mesh.vertex[n - 1], mesh.vertex[n + 1], mesh.vertex[n + w - 1], mesh.vertex[n + w]]

// vertex on the border
else 
	if n < width: // upper
		if (n + 1)%4 == 0: // upper and right
			neighbours = [mesh.vertex[n - 1], mesh.vertex[n + w - 1], mesh.vertex[n + w]]

		else if n%4 == 0 // upper and left
			neighbours = [mesh.vertex[n + 1], mesh.vertex[n + w]]

		else: // just upper
			neighbours = [mesh.vertex[n - 1], mesh.vertex[n + 1], mesh.vertex[n + w - 1], mesh.vertex[n + w]]

	else if n >= (height-1) * width: // lower
		if n == (n + 1)%4 == 0: //l ower and right
			neighbours = [mesh.vertex[n - w], mesh.vertex[n - 1]]

		else if n == n%4 == 0: // lower and left
			neighbours = [mesh.vertex[n - w], mesh.vertex[n - w + 1], mesh.vertex[n + 1]]

		else: // just lower
			neighbours = [mesh.vertex[n - w], mesh.vertex[n - w + 1], mesh.vertex[n - 1], mesh.vertex[n + 1]]

	else if (n + 1)%4 == 0: // right
		neighbours = [mesh.vertex[n - w], mesh.vertex[n - 1], mesh.vertex[n + w - 1], mesh.vertex[n + w]]

	else if n%4 == 0: // left
		neighbours = [mesh.vertex[n - w], mesh.vertex[n - w + 1], mesh.vertex[n + 1], mesh.vertex[n + w]]


__________________________________________________________________________________________________________________________________________

2)

// if current vertex is at any border it won't have one or more neighbours, so if the neighbour don't exist it should be skipped (if condition)

if !(n < width): // not on upper border
	neighbor = mesh.vertex[n-w] // upper neighbor skip
	forceNeighbor = -k * (deltaX(vertex, neighbor)) * getSinBetween(vertex, neighbor);
	acceleration += forceNeighbor

if !(n < width) or !((n + 1) % width == 0): // not on upper or right border skip
	neighbor = mesh.vertex[n-w+1] // upper diagonal neighbor
	forceNeighbor = -k * (deltaX(vertex, neighbor)) * getSinBetween(vertex, neighbor);
	acceleration += forceNeighbor

if !(n % width == 0): // not on left border skip
	neighbor = mesh.vertex[n-1] // left neighbor
	forceNeighbor = -k * (deltaX(vertex, neighbor)) * getSinBetween(vertex, neighbor);x
	acceleration += forceNeighbor

if !((n + 1) % width == 0): // not on left border skip
	neighbor = mesh.vertex[n+1] // right neighbor
	forceNeighbor = -k * (deltaX(vertex, neighbor)) * getSinBetween(vertex, neighbor);
	acceleration += forceNeighbor

if !(n >= (height-1) * width) or !(n % width == 0): // not on lower or left border skip
	neighbor = mesh.vertex[n+w-1] // lower digonal neighbor 
	forceNeighbor = -k * (deltaX(vertex, neighbor)) * getSinBetween(vertex, neighbor);
	acceleration += forceNeighbor

if !(n >= (height-1) * width ): // not on lower border skip
	neighbor = mesh.vertex[n+w] // lower neighbor
	forceNeighbor = -k * (deltaX(vertex, neighbor)) * getSinBetween(vertex, neighbor);
	acceleration += forceNeighbor


