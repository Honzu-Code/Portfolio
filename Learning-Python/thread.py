import logging
import threading
import time
import concurrent.futures

class FakeDatabase:
    def __init__(self):
        self.value = 0
        self._lock = threading.Lock()

    def update(self, name):
        logging.info("Thread %s: starting update", name)
        with self._lock:
            local_copy = self.value
            local_copy += 1
            time.sleep(0.1)
            self.value = local_copy
        logging.info("Thread %s: finishing update", name)




def first_function(name):
    logging.info("Thread %s: starting",name)
    time.sleep(2)
    logging.info("Thread %s: finishing",name)

if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO, \
                        datefmt="%H:%M:%S")
    threads = list()
    for index in range(3):
        logging.info("Main    : create and start thread %d.", index)
        x = threading.Thread(target=first_function, args=(index,))
        threads.append(x)
        x.start()

    for index, thread in enumerate(threads):
        logging.info("Main    : before joining thread %d.", index)
        thread.join()
        logging.info("Main    : thread %d done", index)

    with concurrent.futures.ThreadPoolExecutor(max_workers=3) as executor:
        executor.map(first_function, range(3))

    database = FakeDatabase()
    logging.info("Testing update. Starting value is %d.", database.value)

    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as executor:
        for index in range(2):
            executor.submit(database.update, index)

    logging.info("Testing update. Ending value is %d.", database.value)
