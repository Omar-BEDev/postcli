#include "core/date-compare.h"
#include <gtest/gtest.h>

TEST(StrToDate, ValidDate) {
    Date d = str_to_date((char *)"2026/12/30");
    EXPECT_EQ(d.year, 2026);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 30);
}

TEST(StrToDate, ZeroPaddedSingles) {
    Date d = str_to_date((char *)"2000/01/01");
    EXPECT_EQ(d.year, 2000);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

TEST(StrToDate, EndOfYear) {
    Date d = str_to_date((char *)"1999/12/31");
    EXPECT_EQ(d.year, 1999);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 31);
}

TEST(IsDateBigger, YearBigger) {
    EXPECT_EQ(is_date_bigger((char *)"2027/01/01", (char *)"2026/12/31"), 1);
}

TEST(IsDateBigger, YearSmaller) {
    EXPECT_EQ(is_date_bigger((char *)"2026/12/31", (char *)"2027/01/01"), 0);
}

TEST(IsDateBigger, MonthBigger) {
    EXPECT_EQ(is_date_bigger((char *)"2026/12/01", (char *)"2026/11/30"), 1);
}

TEST(IsDateBigger, MonthSmaller) {
    EXPECT_EQ(is_date_bigger((char *)"2026/11/30", (char *)"2026/12/01"), 0);
}

TEST(IsDateBigger, DayBigger) {
    EXPECT_EQ(is_date_bigger((char *)"2026/12/31", (char *)"2026/12/30"), 1);
}

TEST(IsDateBigger, DaySmaller) {
    EXPECT_EQ(is_date_bigger((char *)"2026/12/30", (char *)"2026/12/31"), 0);
}

TEST(IsDateBigger, EqualDates) {
    EXPECT_EQ(is_date_bigger((char *)"2026/12/30", (char *)"2026/12/30"), 0);
}

TEST(IsDateSmall, YearSmaller) {
    EXPECT_EQ(is_date_small((char *)"2026/12/31", (char *)"2027/01/01"), 1);
}

TEST(IsDateSmall, YearBigger) {
    EXPECT_EQ(is_date_small((char *)"2027/01/01", (char *)"2026/12/31"), 0);
}

TEST(IsDateSmall, MonthSmaller) {
    EXPECT_EQ(is_date_small((char *)"2026/11/30", (char *)"2026/12/01"), 1);
}

TEST(IsDateSmall, MonthBigger) {
    EXPECT_EQ(is_date_small((char *)"2026/12/01", (char *)"2026/11/30"), 0);
}

TEST(IsDateSmall, DaySmaller) {
    EXPECT_EQ(is_date_small((char *)"2026/12/30", (char *)"2026/12/31"), 1);
}

TEST(IsDateSmall, DayBigger) {
    EXPECT_EQ(is_date_small((char *)"2026/12/31", (char *)"2026/12/30"), 0);
}

TEST(IsDateSmall, EqualDates) {
    EXPECT_EQ(is_date_small((char *)"2026/12/30", (char *)"2026/12/30"), 0);
}
