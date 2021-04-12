#！/bin/bash

cmake -B build . -DFAISS_ENABLE_GPU=OFF -DBUILD_TESTING=OFF -DPython_EXECUTABLE=/home/eason/anaconda3/bin/python3.7
make -C build demo_ivfpq_indexing
