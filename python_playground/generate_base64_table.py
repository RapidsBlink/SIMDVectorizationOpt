if __name__ == '__main__':
    set_A2Z = [ord('A') + i for i in xrange(26)]
    set_a2z = [ord('a') + i for i in xrange(26)]
    set_0to9 = [ord('0') + i for i in xrange(10)]
    set_plus = [ord('+')]
    set_slash = [ord('/')]
    fold_res = reduce(lambda l, r: l + r, [set_A2Z, set_a2z, set_0to9, set_plus, set_slash], [])

    # 1st: encoding ascii translation table
    print ', '.join(
        map(lambda e: "'" + e + "'",
            map(chr, fold_res)))

    # 2nd: decoding ascii translation table
    print 'total number:', max(fold_res) + 1
    lst = [-1 for i in xrange(max(fold_res) + 1)]
    for idx, ele in enumerate(fold_res):
        lst[ele] = idx
    print ', '.join(map(str, lst))
