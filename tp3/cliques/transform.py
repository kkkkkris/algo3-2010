import glob, re

numbers = re.compile('\d+')

def construirGrafo(grafo, size):
    for x in range(1, size+1):
        grafo[str(x)] = set()

def transformar(clique, salida):
    inicio = True
    grafo = {}
    ntotal = -2
    leyenda = ''
    for line in clique:
        if not inicio:
            arista = numbers.findall(line)
            grafo[arista[0]].add(arista[1])
            grafo[arista[1]].add(arista[0])
        elif line[0] == 'p':
            ntotal = numbers.findall(line)
            construirGrafo(grafo, int(ntotal[0]))
            inicio = False
        else:
            leyenda += line
    salida.write(ntotal[0] + '\n')
    keys = grafo.keys()
    keys.sort(key=lambda z: int(z))
    for k in keys:
        x = grafo[k]
        x = list(x)
        x.sort(key=lambda z: int(z))
        salida.write(str(len(x)) + ' ' + ' '.join(x) + '\n')
    
    return leyenda
    
cliques = glob.glob('*.clq')
resultados = []
for clique in cliques:
    arc = file(clique, 'r')
    sal = file(clique+'.in', 'w')
    try:
        leyenda = transformar(arc, sal)
    except:
        print clique
    temp = file(clique+'.in.exp', 'w')
    temp.write(leyenda)
    temp.close()
    sal.write('-1')
    sal.close()
    arc.close()
