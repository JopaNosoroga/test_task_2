#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <utility>
class GeometryFigure {
public:
  virtual double getSquare() const = 0;
  virtual ~GeometryFigure() {}
};

class Rectangle : public GeometryFigure {
public:
  Rectangle(double w, double h) {
    if (w >= 0 && h >= 0) {
      width = w;
      height = h;
    } else {
      height = 0;
      width = 0;
    }
  }

  ~Rectangle() {}
  double getSquare() const override { return width * height; }

private:
  double width;
  double height;
};

class Circle : public GeometryFigure {
public:
  Circle(double r) {
    if (r >= 0)
      radius = r;
    else
      radius = 0;
  }
  ~Circle() {}
  double getSquare() const override { return radius * radius * PI; }

private:
  double radius;
  static constexpr double PI = 3.14;
};

class Triangle : public GeometryFigure {
public:
  Triangle(double a_1, double a_2, double a_3) {
    if (a_1 >= 0 && a_2 >= 0 && a_3 >= 0) {
      angle_3 = a_3;
      angle_2 = a_2;
      angle_1 = a_1;
    } else {
      angle_1 = 0;
      angle_2 = 0;
      angle_3 = 0;
    }
  }
  ~Triangle() {}
  double getSemiPerimeter() const { return (angle_3 + angle_2 + angle_1) / 2; }

  double getSquare() const override {
    double P = getSemiPerimeter();
    if (angle_1 == 0 || angle_2 == 0 || angle_3 == 0)
      return 0;
    return std::sqrt(P * (P - angle_1) * (P - angle_2) * (P - angle_3));
  };

private:
  double angle_1;
  double angle_2;
  double angle_3;
};

void bubbleSort(GeometryFigure **arr, int count) {
  for (int i = 0; i < count; i++) {
    bool is_swap = false;
    for (int j = 0; j < count - i - 1; j++) {
      if (arr[j]->getSquare() < arr[j + 1]->getSquare()) {
        auto temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        is_swap = true;
      }
    }
    if (!is_swap)
      break;
  }
}

TEST(TestClass, Sorting_1) {
  GeometryFigure *arr[5];
  arr[0] = new Rectangle(10.8, 2);
  arr[1] = new Rectangle(30, 50);
  arr[2] = new Rectangle(2, 5);
  arr[3] = new Rectangle(9, 10);
  arr[4] = new Rectangle(2, 8);
  bubbleSort(arr, 5);
  ASSERT_EQ(arr[0]->getSquare(), 1500);
  ASSERT_EQ(arr[1]->getSquare(), 90);
  ASSERT_EQ(arr[2]->getSquare(), 21.6);
  ASSERT_EQ(arr[3]->getSquare(), 16);
  ASSERT_EQ(arr[4]->getSquare(), 10);
}

TEST(TestClass, Sorting_2) {
  GeometryFigure *arr[5];
  arr[0] = new Triangle(10, 12.2, 3);
  double semiPer_1 = (10 + 12.2 + 3) / 2;
  arr[1] = new Rectangle(5.5, 2);
  arr[2] = new Circle(8.2);
  arr[3] = new Triangle(0, 0, 0);
  arr[4] = new Rectangle(0, 0);
  const double PI = 3.14;
  bubbleSort(arr, 5);

  ASSERT_EQ(arr[0]->getSquare(), 8.2 * 8.2 * PI);
  ASSERT_EQ(arr[1]->getSquare(),
            std::sqrt(semiPer_1 * (semiPer_1 - 10) * (semiPer_1 - 12.2) *
                      (semiPer_1 - 3)));
  ASSERT_EQ(arr[2]->getSquare(), 5.5 * 2);
  ASSERT_EQ(arr[3]->getSquare(), 0);
  ASSERT_EQ(arr[4]->getSquare(), 0);
  for (int i = 0; i < 5; i++)
    delete arr[i];
}

TEST(TestClass, Sorting_3) {
  GeometryFigure *arr[10];
  arr[0] = new Triangle(10, 12.2, 3);
  double semiPer_1 = (10 + 12.2 + 3) / 2;
  arr[1] = new Rectangle(5.5, 2);
  arr[2] = new Circle(8.2);
  arr[3] = new Triangle(0, 0, 0);
  arr[4] = new Rectangle(0, 0);
  arr[5] = new Rectangle(10.8, 2);
  arr[6] = new Rectangle(30, 50);
  arr[7] = new Rectangle(2, 5);
  arr[8] = new Rectangle(9, 10);
  arr[9] = new Rectangle(2, 8);
  const double PI = 3.14;
  std::cout << "Изначальный массив: \n";
  for (int i = 0; i < 10; i++)
    std::cout << "square: " << arr[i]->getSquare() << '\n';
  bubbleSort(arr, 10);
  std::cout << "Отсортированный массив \n";
  for (int i = 0; i < 10; i++)
    std::cout << "square: " << arr[i]->getSquare() << '\n';
  ASSERT_EQ(arr[0]->getSquare(), 30 * 50);
  ASSERT_EQ(arr[1]->getSquare(), 8.2 * 8.2 * PI);
  ASSERT_EQ(arr[2]->getSquare(), 9 * 10);
  ASSERT_EQ(arr[3]->getSquare(), 10.8 * 2);
  ASSERT_EQ(arr[4]->getSquare(), 2 * 8);
  ASSERT_EQ(arr[5]->getSquare(),
            std::sqrt(semiPer_1 * (semiPer_1 - 10) * (semiPer_1 - 12.2) *
                      (semiPer_1 - 3)));
  ASSERT_EQ(arr[6]->getSquare(), 5.5 * 2.0);
  ASSERT_EQ(arr[7]->getSquare(), 2 * 5);
  ASSERT_EQ(arr[8]->getSquare(), 0);
  ASSERT_EQ(arr[9]->getSquare(), 0);

  for (int i = 0; i < 10; i++)
    delete arr[i];
}

TEST(TestClass, Sorting_4) {
  GeometryFigure *arr[1];
  arr[0] = new Rectangle(1, 5);
  bubbleSort(arr, 1);
  ASSERT_EQ(arr[0]->getSquare(), 5);
  delete arr[0];
}

TEST(TestClass, Sorting_5) {
  GeometryFigure *arr[0];
  bubbleSort(arr, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
