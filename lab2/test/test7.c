int test7(int x) {
    int xx, a;
  
    xx = x << 1;
    xx = (xx & (~((x >> 31) ^ (xx >> 31)))) + ((((x >> 31) ^ (xx >> 31)) << 31) ^ ((~(x >> 31)) & ((x >> 31) ^ (xx >> 31))));

    a = x * 2;

    assert(xx != 0x80000000);
}