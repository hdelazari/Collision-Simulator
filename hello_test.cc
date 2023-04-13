#include "physics.cpp"
#include <gtest/gtest.h>

bool compareCircle(Circle c1, Circle c2) {
  if (c1.position.x!=c2.position.x) {return false;}
  if (c1.position.y!=c2.position.y) {return false;}
  if (c1.velocity.x!=c2.velocity.x) {return false;}
  if (c1.velocity.y!=c2.velocity.y) {return false;}
  return true;
}

// Demonstrate some basic assertions.
TEST(Blah, BasicAssertions) {

  struct {
      Circle c;
      Bounds b;
      Circle expected;
  } tests[] = {
      {
          {{0.4, 100}, {-1, 0}, 1, 0},
          {1000, 1000},
          {{1.6, 100}, {1, 0}, 1, 0},
      }
  };
  
  for (auto test : tests) {
    updateBounds(test.c,test.b,{0,0.1});
    if (!compareCircle(test.c,test.expected)) {
      printCircle(test.c);
      printCircle(test.expected);
      printf("*\n");
      EXPECT_EQ(1,0);
  }



  }

}
