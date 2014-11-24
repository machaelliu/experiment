#ifndef _BIG_FLOAT_H_
#define _BIG_FLOAT_H_

#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;
namespace n_big_float
{

    /* 定义一个类，表示大的浮点数 */
    /****************************************************************************
      @ 要重载运算符 >> 用 cin 来输入
      @ 要重载运算符 << 用 cout << 来输出，不包含前导和结尾 0
      @ 要重载运算符 +，用来计算两个 BigFloat 的和，结果还是 BigFloat 类型
      @ 要重载运行符 *，计算两个BigFloat 类型的乘积
      @ 计算时要注意 digits 为 +INF 和 -INF 的情况
     ****************************************************************************/
    class BigFloat
    {
        friend ostream &operator<<(ostream &os, const BigFloat &bigNum);
        friend istream &operator>>(istream &is, BigFloat &bigNum);

        public:
        BigFloat():sign('+'), digits("0"), exp(0)
        {
        }

        BigFloat(double num):exp(0)
        {
            if (num >= 0)
            {
                sign = '+';
            }
            else
            {
                sign = '-';
                num = -num;
            }

            ostringstream ss;
            ss << num;
            if (!formalize(ss.str()))
            {
                cerr << "wrong big number format" << endl;
                exit(-1);
            }
        }

        private:

        // 符号位，'+' 或 '-'
        char sign;
        
        // 尾数，规格化后，保存的最大长度为 MAX_MANT_LEN，超过 MAX_MANT_LEN 的部分直接截去
        string digits;

        // 指数，范围为 [-MAX_EXP, +MAX_EXP]，超过这个范围认为是正无穷和负无穷
        int exp; 

        static const int MAX_EXP = 3;
        static const string::size_type MAX_MANT_LEN = 500;

        private:
        bool formalize(string);
        string addBigInt(const string &num1, const string &num2, bool &hasCarry)
    };

    // 输入输出操作符
    ostream& operator<<(ostream &os, const BigFloat &num);
    istream& operator>>(istream &is, BigFloat &num);
}

#endif
