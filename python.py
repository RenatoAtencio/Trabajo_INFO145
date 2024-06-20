import heapq
import math
from collections import defaultdict, Counter

# Función para construir el árbol de Huffman
def build_huffman_tree(freq):
    heap = [[weight, [symbol, ""]] for symbol, weight in freq.items()]
    heapq.heapify(heap)
    while len(heap) > 1:
        lo = heapq.heappop(heap)
        hi = heapq.heappop(heap)
        for pair in lo[1:]:
            pair[1] = '0' + pair[1]
        for pair in hi[1:]:
            pair[1] = '1' + pair[1]
        heapq.heappush(heap, [lo[0] + hi[0]] + lo[1:] + hi[1:])
    return sorted(heapq.heappop(heap)[1:], key=lambda p: (len(p[-1]), p))

# Función para obtener los códigos de Huffman
def huffman_coding(gaps):
    freq = Counter(gaps)
    huffman_tree = build_huffman_tree(freq)
    huffman_dict = {symbol: code for symbol, code in huffman_tree}
    return huffman_dict

# Función para codificar los gaps usando Huffman
def encode_gaps(gaps, huffman_dict):
    return ''.join(huffman_dict[gap] for gap in gaps)

# Función para decodificar los gaps usando Huffman
def decode_gaps(encoded_gaps, huffman_dict):
    reverse_dict = {v: k for k, v in huffman_dict.items()}
    decoded = []
    buffer = ""
    for bit in encoded_gaps:
        buffer += bit
        if buffer in reverse_dict:
            decoded.append(reverse_dict[buffer])
            buffer = ""
    return decoded

# Función para crear la estructura "sample"
def create_sample(arr, m):
    n = len(arr)
    b = math.ceil(n / m)
    sample = [arr[i * b] for i in range(m)]
    return sample, b

# Función para reconstruir el valor original a partir del gap-coding
def reconstruct_value(gaps, index):
    value = gaps[0]
    for i in range(1, index + 1):
        value += gaps[i]
    return value

# Función para buscar un número en el arreglo original usando sample y gap-coding
def search_number(gaps, sample, number, b):
    # Búsqueda binaria en el sample para encontrar el rango
    low, high = 0, len(sample) - 1
    while low <= high:
        mid = (low + high) // 2
        if sample[mid] == number:
            return mid * b
        elif sample[mid] < number:
            low = mid + 1
        else:
            high = mid - 1

    # Determinar el rango en gaps
    start = max(0, high * b)
    end = min(len(gaps), (low + 1) * b)

    # Recorrer el arreglo gap-coded dentro del rango
    for i in range(start, end):
        if reconstruct_value(gaps, i) == number:
            return i

    return -1

# Ejemplo de ejecución

# Arreglo de ejemplo
original_array = [2, 7, 10, 12, 12, 16]

# Aplicar Gap-Coding
gaps = [original_array[0]] + [original_array[i] - original_array[i - 1] for i in range(1, len(original_array))]

print("Original Array:")
print(original_array)

print("\nGap-Coded Array:")
print(gaps)

# Construir el árbol de Huffman y obtener los códigos
huffman_dict = huffman_coding(gaps)
print("\nCódigos de Huffman:")
print(huffman_dict)

# Codificar los gaps usando Huffman
encoded_gaps = encode_gaps(gaps, huffman_dict)
print("\nGaps Codificados:")
print(encoded_gaps)

# Decodificar los gaps para verificar la correcta codificación
decoded_gaps = decode_gaps(encoded_gaps, huffman_dict)
print("\nGaps Decodificados:")
print(decoded_gaps)

# Crear la estructura "sample"
m = 3
sample, b = create_sample(original_array, m)
print("\nSample Array:")
print(sample)

# Ejemplo de búsqueda en el arreglo original usando la estructura "sample" y Gap-Coding
number_to_search = 10
index = search_number(gaps, sample, number_to_search, b)
print(f"\nNúmero {number_to_search} encontrado en el índice {index} del arreglo original.")
