method method1(x: int, y: int) returns (z: int)
// Add a precondition here.
// requires x < 0 && y > 0
requires x > 0
ensures z > 0
{
   if x < 0
     { return y; }
   else
     { return x; }
}
