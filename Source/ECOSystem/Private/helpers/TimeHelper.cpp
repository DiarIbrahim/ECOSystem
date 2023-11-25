// All rights received for Diar Games contact via : Email : diarm999@gmail.com    Linkedin : https://www.linkedin.com/in/diar-ibrahim-ali/ Twitter : https://twitter.com/diar__Ibrahim


#include "Helpers/TimeHelper.h"

//  365/30 
static float mounthRatio = 30.41666666666667;


int32 UTimeHelper::AgeAsYear(const int32& age)
{
    return age/365;
}

int32 UTimeHelper::AgeAsMonth(const int32& age)
{
    return age/ mounthRatio;
}

FString YearsString(int32 Years) {
    if (Years <= 0) return "";
    else if (Years == 1) {
        return " Year ";
    }
    return " Years ";
}

FString monthString(int32 months) {
    if (months <= 0) return "";
    else if (months == 1) {
        return " Month ";
    }
    return " Months ";
}
FString DayString(int32 days) {
    if (days <= 0) return "";
    else if (days == 1) {
        return " Day ";
    }
    return " Days ";
}

FString UTimeHelper::AgeToString(const int32& age, bool bIncludeMonth, bool bIncludeDays)
{
    int32 years = AgeAsYear(age);
    int32 months = AgeAsMonth(age) - (12 * years);
    int32 days = age - (mounthRatio * months) - (years * 12 * mounthRatio);
    FString Result;

    if (years > 0) {
        Result.Append(FString::FromInt(years)).Append(YearsString(years));
    }
    if (bIncludeMonth && months > 0) {
        Result.Append(FString::FromInt(months)).Append(monthString(months));
    }
    if (bIncludeDays && days > 0)
    {
        Result.Append(FString::FromInt(days)).Append(DayString(days));
    }

    return Result;
}
