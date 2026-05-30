# Compile: python3 collections_basics.py
# Output:
# [('the', 3), ('quick', 1), ('brown', 1)]
# {'A', 'B', 'C', 'D'}

from collections import Counter, defaultdict, deque, namedtuple, OrderedDict

words = "the quick brown fox jumps over the lazy dog the".split()
freq = Counter(words)
print(freq.most_common(3))

graph: dict = defaultdict(list)
for u, v in [("A","B"), ("A","C"), ("B","D")]:
    graph[u].append(v)

queue = deque(["A"])
visited = set()
while queue:
    node = queue.popleft()
    if node not in visited:
        visited.add(node)
        queue.extend(graph[node])
print(visited)

# namedtuple
Point = namedtuple("Point", ["x", "y"])
p = Point(3, 4)
print(p.x, p.y, p._asdict())
print(p._replace(x=10))

# deque as fixed-size sliding window
window = deque(maxlen=3)
for n in range(6):
    window.append(n)
    print(f"window: {list(window)}")
