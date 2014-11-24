#include "big_float.h"

namespace n_big_float
{
    // 浮点尾数相加，相当于右对齐相加
    string BigFloat::addBigInt(const string &num1, const string &num2, bool &hasCarry)
    {
        hasCarry= false;
        int carry = 0;
        string::size_type size1 = num1.size();

        string::size_type size2 = num2.size();
        string::size_type size = 0; 
        string::size_type lZeroNums = 0; // 较短的数要补的前导 0 的个数
        if (size1 > size2)
        {
            lZeroNums = size1 - size2;
            string zeros(lZeroNums, '0');
            num2 = zeros + num2;
            size = size1;
        }
        else
        {
            lZeroNums = size2 - size1;
            string zeros(lZeroNums, '0');
            num2 = zeros + num1;
            size = size2;
        }

        string sum(num1);

        // 长度相同的两数相加
        for (string::size_type ix = size; ix >= 0; --ix)
        {
            sum[ix] += num2[ix] - '0' + carry;
            if (sum[ix] > '9')
            {
                sum[ix] -= 10;
                carry = 1;
            }
        }

        if (1 == carry)
        {

        }

    }

    // 检查给定参数是否合法，若合法则规格化，参数不能是引用，因为可能会对 digits 
    // 本身规格化
    bool BigFloat::formalize(string strNum)
    {
        bool mantAllZero = true; // 标识尾数部分是否全 0 
        bool intAllZero = true; // 标识尾数部分是否全 0
        string::size_type intFstNotZeroIx = 0; // 整数部分左数第一个不为0的索引
        string::size_type mantFstNotZeroIx = 0; // 尾数部分左数第一个不为0的索引
        char givenSign = '+';
        string::size_type numBegIx = 0;
        string::size_type str_size = strNum.size();
        string::size_type backNotZeroIx; // 从尾部往前数第一个不为0的位的索引

        // 处理符号位
        if ('+' == strNum[0]|| '-' == strNum[0] )
        {
            if (str_size < 2)
            {
                return false;
            }
            givenSign = strNum[0];
            numBegIx = 1;
        }
        sign = givenSign;

        string::size_type dotIx = strNum.find('.', numBegIx);

        // 以小数点结尾(包含了数字部分只含小数点的情况)，数字非法
        if (dotIx == str_size - 1)
        {
            return false;
        }
        // 除符号外以小数点开头，即数字部分只有小数
        else if (dotIx == numBegIx)
        {
            for (string::size_type ix=dotIx+1; ix != str_size; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (mantAllZero && strNum[ix] != '0')
                {
                    mantAllZero = false;
                    mantFstNotZeroIx = ix;
                }
            }

            // 尾数全为 0
            if (mantAllZero)
            {
                digits = "0";
            }
            else   // 尾数不全为 0
            {
                // 去掉尾部的 0 
                for (string::size_type ix = str_size - 1; ; --ix)
                {
                    if (strNum[ix] != '0')
                    {
                        backNotZeroIx = ix;
                        break;
                    }
                }

                exp = dotIx - mantFstNotZeroIx + 1;
                digits = strNum.substr(mantFstNotZeroIx, backNotZeroIx - mantFstNotZeroIx + 1); 
                //cout << "backNotZeroIx:" << backNotZeroIx << endl;
                //cout << "mantFstNotZeroIx:" << mantFstNotZeroIx << endl;
                //cout << "digits:" << digits << endl;
                //cout << "exp:" << exp << endl;
            }
        }
        // 不存在小数点，只有整数
        else if (dotIx == strNum.npos)
        {
            for (string::size_type ix = numBegIx; ix != str_size; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (intAllZero && strNum[ix] != '0')
                {
                    intAllZero = false;
                    intFstNotZeroIx = ix;
                }
            }

            if (intAllZero)
            {
                digits = "0";
            }
            else
            {
                // 舍去整数中的前导0，并将小数点移到数字最前端
                exp = str_size - intFstNotZeroIx;

                // 去掉尾部的 0 
                for (string::size_type ix = str_size - 1; ; --ix)
                {
                    if (strNum[ix] != '0')
                    {
                        backNotZeroIx = ix;
                        break;
                    }
                }

                digits = strNum.substr(intFstNotZeroIx, backNotZeroIx - intFstNotZeroIx + 1);
            }

        }
        // 存在小数点，既有整数部分也有小数部分
        else 
        {
            // 检查整数部分
            for (string::size_type ix = numBegIx; ix != dotIx; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (intAllZero && strNum[ix] != '0')
                {
                    intAllZero = false;
                    intFstNotZeroIx = ix;
                }
            }

            // 检查小数部分
            for (string::size_type ix = dotIx + 1; ix != str_size; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (mantAllZero && strNum[ix] != '0')
                {
                    mantAllZero = false;
                    mantFstNotZeroIx = ix;
                }
            }

            if (intAllZero) // 整数部分全为 0 
            {
                //cout << "1" << endl;
                if (mantAllZero) // 小数部分全 0
                {
                    digits = "0";
                }
                else // 小数部分不全为0，但可能含前导 0
                {
                    // 整数部分全0，尾数有前导0，将整数部分和尾数前导0去掉后，将
                    // 小数点放到数字最前面，对指数进行相应调整
                    exp = dotIx - mantFstNotZeroIx + 1;

                    // 去掉尾部的 0 
                    for (string::size_type ix = str_size - 1; ; --ix)
                    {
                        if (strNum[ix] != '0')
                        {
                            backNotZeroIx = ix;
                            break;
                        }
                    }
                    digits = strNum.substr(mantFstNotZeroIx, backNotZeroIx - mantFstNotZeroIx + 1);
                }
            }
            // 整数部分不全为 0 
            else
            {
                if (mantAllZero) // 整数不全为0， 小数全 0
                {
                    // 去掉整数尾部的 0 
                    for (string::size_type ix = dotIx -1; ix != intFstNotZeroIx; --ix)
                    {
                        if (strNum[ix] != '0')
                        {
                            backNotZeroIx = ix;
                            break;
                        }
                    }

                    exp = dotIx - intFstNotZeroIx;
                    digits = strNum.substr(intFstNotZeroIx, backNotZeroIx - intFstNotZeroIx + 1);
                }
                else // 整数、小数部分都不全为0
                {
                    // 去掉小数尾部的 0 
                    for (string::size_type ix = str_size - 1; ix != dotIx ; --ix)
                    {
                        if (strNum[ix] != '0')
                        {
                            backNotZeroIx = ix;
                            break;
                        }
                    }

                    exp = dotIx - intFstNotZeroIx;

                    // 去掉小数点
                    digits = strNum.substr(intFstNotZeroIx, dotIx - intFstNotZeroIx);
                    digits += strNum.substr(dotIx + 1, backNotZeroIx - dotIx);
                }

            }
        }

        // 处理边界情况
        if (exp > MAX_EXP)
        {
            // 负无穷用 -INF，正无穷用 +INF
            digits = "INF";
        }
        else if (exp < -MAX_EXP)
        {
            digits = "0";
        }

        if ("0" == digits || "INF" == digits)
        {
            exp = 0;
        } 
        else if (digits.size() > MAX_MANT_LEN)
        {
            digits = digits.substr(0, 500);
        }

        return true;
    } // end of formalize

    ostream& operator<<(ostream& os, const BigFloat &bigNum)
    {
        if (1 == bigNum.digits.size())
        {
            if ('-' == bigNum.sign && bigNum.digits != "0")
            {
                os << '-';
            }
            os << bigNum.digits << ".0";

            if (bigNum.digits != "0" && bigNum.exp != 1)
            {
                os << " " << "E" << bigNum.exp - 1;
            }

            os << endl;
        }
        else if ("INF" == bigNum.digits)
        {
            os << bigNum.sign << "INF" << endl;
        }
        else
        {
            if ('-' == bigNum.sign)
            {
                os << '-';
            }

            // 输出标准科学表示法，如 3.456 E5
            os << bigNum.digits[0] << "." << bigNum.digits.substr(1);

            if (bigNum.exp != 1)
            {
                os << " " << "E" << bigNum.exp - 1;
            }

            os << endl;
        }

        return os;
    }

    ///* 算术左移 */
    //BigFloat& BigFloat::operator<<=(int shitfs)
    //{
    //    if (digits != "0" && digits != "INF" && shitfs != 0)
    //    {
    //        exp += shitfs;

    //        if (exp > MAX_EXP)
    //        {
    //            digits = "INF";
    //            exp = 0;
    //        }
    //        else if (exp < MAX_EXP)
    //        {
    //            digits = "0";
    //            exp = 0;
    //        }
    //    }

    //    return *this;
    //}

    //// 算术右移
    //BigFloat& BigFloat::operator>>=(int shitfs)
    //{
    //    (*this) <<= -shitfs;
    //    return *this;
    //}


    bool operator==(const BigFloat &bigNum1, const BigFloat &bigNum2)
    {
        if (bigNum1.sign != bigNum2.sign)
        {
            return false;
        }

        if (bigNum1.digits != bigNum2.digits)
        {
            return false;
        }

        if (bigNum1.exp != bigNum2.exp)
        {
            return false;
        }

        return true;
    }

    istream &operator>>(istream &is, BigFloat &bigNum)
    {
        string num;
        is >> num;

        if (is)
        {
            if (!bigNum.formalize(num))
            {
                // 输入格式不对，设置流的错误状态
                is.clear(istream::failbit);
            }
        }

        return is;
    }


} // end of namespace


