/*
#!/bin/bash
for ((t=1; ; t++)); do
    echo "Test $t"
    ./gen 50 > in/in${t}.txt
    ./brute < in/in${t}.txt > out1.txt
    ./sol < in/in${t}.txt > out2.txt
    if ! diff -q out1.txt out2.txt >/dev/null; then
        echo "Mismatch found on test $t!"
        cat in/in${t}.txt
        diff out1.txt out2.txt
        break
    fi
done
# also for times, use this:
# #ifndef ONLINE_JUDGE
# clock_t tStart = clock();
# #endif
# void runtime() {
# #ifndef ONLINE_JUDGE
#     double elapsed =
#         (double)(clock() - tStart) / CLOCKS_PER_SEC;

#     fprintf(stderr,
#             ">> Runtime: %.10fs\n",
#             elapsed);
# #endif
# }
*/
