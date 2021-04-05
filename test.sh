ITEREATIONS="1000000 10000000 100000000 1000000000"
THREADS="1 2 4 6 8"
NRUNS="20"
for IT in $ITEREATIONS; do
    for TH in $THREADS; do
        for R in $(seq 1 $NRUNS); do
            ./PI -p $IT -t $TH -b
        done
    done
done | tee output_file_omp.csv

