# Compile: python3 abstract_base_classes.py
# Output:
# {'id': 0}
# {'id': 1}
# {'id': 2}

from abc import ABC, abstractmethod
from typing import Iterator

class DataSource(ABC):
    @abstractmethod
    def connect(self) -> None: ...

    @abstractmethod
    def read_batch(self, size: int) -> list[dict]: ...

    @abstractmethod
    def close(self) -> None: ...

    def read_all(self, batch_size: int = 2) -> Iterator[list[dict]]:
        self.connect()
        try:
            while batch := self.read_batch(batch_size):
                yield batch
        finally:
            self.close()

class MemorySource(DataSource):
    def __init__(self, data: list[dict]):
        self._data = data
        self._pos = 0

    def connect(self) -> None: pass
    def close(self) -> None:   pass

    def read_batch(self, size: int) -> list[dict]:
        batch = self._data[self._pos:self._pos + size]
        self._pos += size
        return batch

src = MemorySource([{"id": i} for i in range(5)])
for batch in src.read_all(batch_size=2):
    for row in batch:
        print(row)

# Can't instantiate ABC with unimplemented methods
try:
    DataSource()
except TypeError as e:
    print(f"Cannot instantiate: {e}")
