- init:
    run: rm -f hw4
    blocker: true

- build:
    run: g++ -Wall -Werror hw4.cpp -o hw4  # timeout: 8
    blocker: true

- case1_simple:
    run: ./hw4 simple.txt
    points: 10
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 [ \r\n]*"                             # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 1 [ \r\n]*"                                # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 2 3 1 [ \r\n]*"                            # timeout: 8
        - expect: _EOF_                                                                        # timeout: 8
    return: 0

- case2_single_hole:
    run: ./hw4 single_hole.txt
    points: 10
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 4 5 6 7 [ \r\n]*"                     # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 6 [ \r\n]*"                                # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 7 6 5 4 3 2 1 [ \r\n]*"                    # timeout: 8
        - expect: _EOF_                                                                       # timeout: 8
    return: 0

- case3_camel:
    run: ./hw4 camel.txt
    points: 20
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 4 5 6 7 8 9 10 [ \r\n]*"               # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 1 9 2 8 3 7 4 6 5 4 6 3 7 2 8 1 9 [ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 6 7 8 3 2 1 10 9 4 5 [ \r\n]*"               # timeout: 8
        - expect: _EOF_                                                                        # timeout: 8
    return: 0
- case4_nothingChanged:
    run: ./hw4 nothingChanged.txt
    points: 15
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 4 5 6 7 8 [ \r\n]*"     # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 5 5 3 1 1 3 [ \r\n]*"          # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 1 2 3 4 5 6 7 8 [ \r\n]*"       # timeout: 8
        - expect: _EOF_                                                           # timeout: 8
    return: 0
- case5_reverse:
    run: ./hw4 reverse.txt
    points: 15
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 4 5 6 7 8 9 10 [ \r\n]*"     # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 9 [ \r\n]*"                           # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 10 9 8 7 6 5 4 3 2 1 [ \r\n]*"       # timeout: 8
        - expect: _EOF_                                                                  # timeout: 8
    return: 0
- case6_empty:
    run: ./hw4 empty.txt
    points: 15
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: [ \r\n]*"     # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 0 [ \r\n]*"                           # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: [ \r\n]*"       # timeout: 8
        - expect: _EOF_                                                                  # timeout: 8
    return: 0
- case7_shuffle:
    run: ./hw4 shuffle.txt
    points: 15
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 [ \r\n]*"     # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 5 6 4 1 2 3 1 5 4 5 6 3 2 1 5 4 2 1 3 5 4 7 5 6 5 4 2 1 3 1 2 5 8 6 4 5 1 12 14 13 12 10 8 7 [ \r\n]*"                           # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 7 5 8 6 11 1 14 2 9 3 4 12 13 15 10 [ \r\n]*"       # timeout: 8
        - expect: _EOF_                                                                  # timeout: 8
    return: 0
