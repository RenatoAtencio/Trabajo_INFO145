
## Objetivo: 
Realizar una busqueda binaria sobre un arreglo X *creciente*, se debe probar con:
 + Arreglo sin comprimir
 + Arreglo con Gap-Coding
 + Arreglo con Gaps comprimidos. Usando Shannon-Fano o Huffman

## Calculos:
 + Representar de forma asintotica o exacta la *cantidad de espacio adicional y coste computacional de las busquedas*
 + Calcular los tiempos, medir empiricamente el espacio en RAM
 + Repetir lo anterior con Arreglos de distintos tamaño
 + Realizar los mismo calculos con Arreglos Lineales y Normales

## Informe: 
 + Introduccion: Contexto del problema, indice
 + Metodologia: Inicializacion de datos, Hipotesis, Costos, Pseudocodigos, Representaciones, Metodos usados para calculos, Largos n de los arrelos
 + Experimentacion: Graficos, tablas, para los resultados
 + Conclusion: Responder Hipotesis, Resumen.
 + Bibliografia
 + Link al repositorio, Codigos consistentes al pseudocodigo, poner las intrucciones de ejecucion en el readme.md

## TODO del codigo
Tener en cuenta que debe ser modular, tener comentarios, y que sea de calidad

 *Inicio*
 + Realizar busqueda binaria sobre esos arreglos y medir tiempos, se debe de calcular el *tiempo teorico* y el experimental
 
 *Gap_Coding*
 La idea del gap coding es usar 2 arreglos auxiliares:
    *GC(X)* que corresponde al arreglo X pero con la diferencia entre cada elemento consecutivo.
    *Sample(X)*: Que corresponde a un pequeño arreglo con algunos valores de X, se establece con un largo m y un espacio b (b deberia depender de m, nosotros definimos eso), b corresponde al salto entre los numero de X que se ponen en el sample, EJ:
        X =         [21, 81, 105, 114, 160, 198]
        GC(X) =     [21, 60, 24, 9, 46, 38]
        Sample(X) = [21, 105, 160]            m=3, b=|X|/m=6/3=2
    En el sample se hace la busqueda binaria para encontrar el *intervalo* en el cual el numero *podria* estar (Se devuelve el intervalo y el *numero inicial*). Una vez con estos indices se puede usar b para transformalos en indices de CG(X)
    Una vez con ese intervalo de GC se puede sumar al numero hasta llegar al numero buscado.

 *Gap-Coding Codificado*
 Para estos se puede usar Huffman o Shannon-Fano
 Ahora para ahorrar espacio se debe pasar el arreglo GC(X) a codigos. 


## DONE
Poner aca las tareas del TODO hechas
 + Crear Arreglo lineal: A[0] = rand(), A[i] = A[i-1] + rand() % ε
 + Crear Arreglo Normal: Se pueden usar librerias
 + Funcion para calcular GC(X)
 + Funcion para calcular el Sample, dado un m y un b (Recordar que m y b es establecido por nosotros)
 + Funcion para obtener el indice y el numero inicial del Sample (Modificacion de la busqueda binaria)
 + Funcion para recorrer GC(X) con el numero obtenido y desde el indice obtenido. Si no se encuentra (suma > um_buscado) se sale simplemente.