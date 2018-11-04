#include <iostream>
#include <string>
#include <sstream>
#include <vector>


#define INPUT_MIN	0			         ///< @brief specified minimum for the user input
#define INPUT_MAX	99999		         ///< @brief specified maximum for the user input
const std::string RUN_TESTS = "test";    ///< @brief used to run tests

/**
 * @brief Returns the input value from the user
 *        Returns -1 if an error occured
 */
int32_t getInput();

/**
 * @brief Converts the input string to an integer
 */
static inline int32_t convertInput(std::string inputString);

/**
 * @brief Returns the reverse of the given input. For example, 123 will return 321
 */
uint32_t calculateReverse(uint32_t input);
std::string calculateReverse(const std::string input);

/**
 * @brief Returns the result of the equation (base^reverse + base^3 - reverse^2 + (base * reverse))
 *        Result is returned as a string to avoid issues of overflowing datatypes
 */
std::string calculateOutput(const uint32_t input, const uint32_t reverse);

/**
* @brief Returns the result of multiplying inputA and inputB as a string
*/
std::string multiply(const std::string &inputA, const std::string &inputB);

/**
* @brief Returns the result of summing inputA and inputB as a string
*/
std::string add(std::string inputA, std::string inputB);

/**
 * @brief Run tests to validate the functions
 */
void runTests();
void test_convertInput();
void test_calculateReverse();
void test_multiply();
void test_add();




/**********************************************************************************************************************/
/*                                                                                                                    */
/*                                                 M A I N   L O O P                                                  */
/*                                                                                                                    */
/**********************************************************************************************************************/

int main()
{
    /** wait for the user to enter a valid number */
    int32_t input = getInput();

    /** validate */
    if (input < 0)
    {
        /** check for 'test' */
        if (input == -2)
        {
            runTests();
            return 0;
        }

        /** error with the input so request the user to enter a new number */
        std::cout << std::endl;
        std::cout << " Error: Invalid Input" << std::endl;
        std::cout << " Enter a valid number between " << INPUT_MIN << " and " << INPUT_MAX << std::endl;
        return -1;
    }

    /** reverse the input */
    uint32_t reverse = calculateReverse(input);

    /** calculate the result */
    std::string result = calculateOutput(input, reverse);

    /** print the result .. X = I^R + I^3 - R^2 + IR */
    std::cout << " Result: " << input << "^" << reverse << " + " <<  input << "^3 - " <<
              reverse << "^2 + (" << input << "*" << reverse << ") is " << result;
    std::cout << std::endl << std::endl;

    return 0;
}




/**********************************************************************************************************************/
/*                                                                                                                    */
/*                                                     I N P U T                                                      */
/*                                                                                                                    */
/**********************************************************************************************************************/

int32_t getInput()
{
    /** prompt the user */
    std::cout << " Enter 'test' to run all tests OR";
    std::cout << " Enter a number (" << INPUT_MIN << "-" << INPUT_MAX << ") :";

    /** initialise values */
    std::string inputString = "";

    /** wait for the input to be entered */
    getline(std::cin, inputString);

    return convertInput(inputString);
}

static inline int32_t convertInput(std::string inputString)
{
    uint32_t input = 0;

    /** convert to a 32bit integer */
    if ((std::stringstream (inputString) >> input))
    {
        /** verify the number is within the specified limits */
        if (input >= INPUT_MIN && input <= INPUT_MAX)
        {
            std::cout << std::endl;
            return input;
        }
    }

    /** check for 'test' */
    if (inputString.compare(RUN_TESTS) == 0)
    {
        return -2;
    }

    return -1;
}


uint32_t calculateReverse(uint32_t input)
{
    /** initialise values */
    uint32_t remainder = 0;
    uint32_t reversed  = 0;

    /** while the input is valid */
    while (input != 0)
    {
        /** calculate the remainder from dividing the input by 10 */
        remainder = input % 10;

        /** add this to reversed number */
        reversed += remainder;

        /** shrink the input and increase the reversed output */
        input /= 10;
        if (input != 0)              //< prevents an additional 0 being added to the end of the revesed output
        {
            reversed *= 10;
        }
    }

    return reversed;
}

std::string calculateReverse(const std::string input)
{
    /** calculate the length */
    int nElements = input.length();

    /** swap characters */
    std::string result = input;

    for (int i = 0; i < nElements / 2; ++i)
    {
        std::swap(result[i], result[nElements - i - 1]);
    }

    return result;
}




/**********************************************************************************************************************/
/*                                                                                                                    */
/*                                               C A L C U L A T I O N                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/

std::string calculateOutput(const uint32_t input, const uint32_t reverse)
{
    /*
     * full equation:
     *   X = I^R + I^3 - R^2 + IR
     *     = xA  + xB  - xC  + xD
     */

    /** calculate I^R (xA) */
    std::string in_xA = std::to_string(input);            //< convert the input to a string
    std::string output = "1";                             //< the first multiplication should be (input * 1)
    for (uint32_t i = 0; i < reverse; ++i)                //< continue to multiply till we reach the exponent
    {
        output = multiply(in_xA, output);
    }

    /** calculate I^3 (xB) */
    uint32_t xB = input * input * input;

    /** calculate R^2 (xC) */
    uint32_t xC = reverse * reverse;

    /** calculate I*R (xD) */
    uint32_t xD = input * reverse;

    /** calculate the sum of the xB - xC + xD */
    uint32_t xBCD = xB - xC + xD;                       //< input^3 will always be larger than reverse^2

    /** add to the output */
    std::string in_xBCD = std::to_string(xBCD);
    output = add(in_xBCD, output);

    return output;
}

std::string multiply(const std::string &inputA, const std::string &inputB)
{
    /** get length of input strings */
    uint32_t lengthA = inputA.size();								//< done to prevent multiple calls to size() further on ..
    uint32_t lengthB = inputB.size();								//< even though the data types are different, the size of the input will not exceed the limit of the uint32

    /** verify lengths */
    if (lengthA == 0 || lengthB == 0)
    {
        return "0";
    }

    /** check if either element is 0 */
    if ((lengthA == 1) && (inputA.compare("0") == 0))
    {
        return "0";
    }
    if ((lengthB == 1) && (inputB.compare("0") == 0))
    {
        return "0";
    }

    /**
     * @note: negative numbers are checked before entering this
     *        this will only work over positive numbers
     */

    /** initialise vector to store all products of A*B */
    std::vector<uint16_t> result(lengthA + lengthB, 0);

    /** calculate the product of A*B */
    for (uint32_t i = 0; i < lengthA; ++i)
    {
        for (uint32_t j = 0; j < lengthB; ++j)
        {
            /** subtract '0' from the character ascii value setting 0 character to 0 value */
            uint8_t valueA = (inputA[i] - '0');
            uint8_t valueB = (inputB[j] - '0');

            /** calculate and store the product in a single array */
            result[i + j + 1] += (valueA * valueB);
        }
    }

    /** if any number is greater than 10, then the remainder character has to carry over to the next */
    for (int32_t i = lengthA + lengthB - 1; i > 0; --i)				//< must be processed backwards due to the way one variable affects the next
    {
        if (result[i] >= 10)
        {
            /** adjust value */
            result[i - 1] += result[i] / 10;

            /** adjust remainder */
            result[i] %= 10;
        }
    }

    /** generate the output string */
    std::string output = "";
    bool write = false;

    for (uint32_t i = 0; i < lengthA + lengthB; ++i)
    {
        /** this flag prevents any leading zeros being returned */
        if (write == false && result[i] > 0)
        {
            write = true;
        }

        if (write)
        {
            /** we have to readjust the character by adding the '0' back as we removed it earlier */
            output += (char)(result[i] + '0');
        }
    }

    return output;
}

std::string add(std::string inputA, std::string inputB)
{
    /** ensure inputB is the longest */
    if (inputB.size() < inputA.size())
    {
        swap(inputA, inputB);
    }

    /** get length of input strings */
    uint32_t lengthA = inputA.size();
    uint32_t lengthB = inputB.size();

    /** initialise result */
    std::string result = "";

    /** reverse both strings */
    std::string revA = calculateReverse(inputA);
    std::string revB = calculateReverse(inputB);
    int nElements = inputA.length();
    int nElements2 = revA.length();

    /** sum the length of the smaller number */
    int remainder = 0;
    for (int i = 0; i < lengthA; ++i)
    {
        int sum = ((revA[i] - '0') + (revB[i] - '0') + remainder);
        result.push_back((sum % 10) + '0');

        /** calculate remainder for the next step */
        remainder = sum / 10;
    }

    /** add remaining of the larger number */
    for (int i = lengthA; i < lengthB; ++i)
    {
        int sum = ((revB[i] - '0') + remainder);
        result.push_back((sum % 10) + '0');

        /** calculate remainder for the next step */
        remainder = sum / 10;
    }

    /** add any remainder */
    if (remainder)
    {
        result.push_back(remainder + '0');
    }

    /** reverse result */
    std::string output = calculateReverse(result);
    return output;
}



/**********************************************************************************************************************/
/*                                                                                                                    */
/*                                                   T E S T I N G                                                    */
/*                                                                                                                    */
/**********************************************************************************************************************/

void runTests()
{
    test_convertInput();
    test_calculateReverse();
    test_multiply();
    test_add();
}

void test_convertInput()
{
    std::cout << std::endl;
    std::cout << " Testing convertInput() .. " << std::endl;

    int32_t in1 = convertInput("10");       //< valid number
    int32_t in2 = convertInput("abc");      //< no number
    int32_t in3 = convertInput("-2");       //< negative number
    int32_t in4 = convertInput("");         //< empty
    int32_t in5 = convertInput(" ");        //< space

    std::string fail1 = "fail (" + std::to_string(in1) + ")";
    std::string fail2 = "fail (" + std::to_string(in2) + ")";
    std::string fail3 = "fail (" + std::to_string(in3) + ")";
    std::string fail4 = "fail (" + std::to_string(in4) + ")";
    std::string fail5 = "fail (" + std::to_string(in5) + ")";

    std::cout << "    10              .. " << ((in1 == 10) ? "pass" : fail1) << std::endl;
    std::cout << "    abc             .. " << ((in2 == -1) ? "pass" : fail2) << std::endl;
    std::cout << "    -2              .. " << ((in3 == -1) ? "pass" : fail3) << std::endl;
    std::cout << "    '' (empty)      .. " << ((in4 == -1) ? "pass" : fail4) << std::endl;
    std::cout << "    ' ' (space)     .. " << ((in5 == -1) ? "pass" : fail5) << std::endl;
}

void test_calculateReverse()
{
    std::cout << std::endl;
    std::cout << " Testing calculateReverse() .. " << std::endl;

    std::string rev1 = calculateReverse("987");      //< valid string
    std::string rev2 = calculateReverse("");         //< empty
    uint32_t rev3 = calculateReverse(12345);         //< valid number
    uint32_t rev4 = calculateReverse(0);             //< zero
    // @note: input is spec'd as uint32

    std::string fail1 = "fail (" + rev1 + ")";
    std::string fail2 = "fail (" + rev2 + ")";
    std::string fail3 = "fail (" + std::to_string(rev3) + ")";
    std::string fail4 = "fail (" + std::to_string(rev4) + ")";

    std::cout << "    '987'           .. " << ((rev1.compare("789") == 0) ? "pass" : fail1) << std::endl;
    std::cout << "    '' (empty)      .. " << ((rev2.compare("") == 0)    ? "pass" : fail2) << std::endl;
    std::cout << "    12345           .. " << ((rev3 == 54321)            ? "pass" : fail3) << std::endl;
    std::cout << "    0               .. " << ((rev4 == 0)                ? "pass" : fail4) << std::endl;
}

void test_multiply()
{
    std::cout << std::endl;
    std::cout << " Testing test_multiply() .. " << std::endl;

    std::string val1 = "10";
    std::string val2 = "2";
    std::string val3 = "0";
    std::string val4 = "";

    std::string mul1 = multiply(val1, val2);
    std::string mul2 = multiply(val2, val1);
    std::string mul3 = multiply(val1, val3);
    std::string mul4 = multiply(val1, val4);

    std::string fail1 = "fail (" + mul1 + ")";
    std::string fail2 = "fail (" + mul2 + ")";
    std::string fail3 = "fail (" + mul3 + ")";
    std::string fail4 = "fail (" + mul4 + ")";

    std::cout << "    '10' * '2'      .. " << ((mul1.compare("20") == 0)  ? "pass" : fail1) << std::endl;
    std::cout << "    '2' * '10'      .. " << ((mul2.compare("20") == 0)  ? "pass" : fail2) << std::endl;
    std::cout << "    '10' * '0'      .. " << ((mul3.compare("0")  == 0)  ? "pass" : fail3) << std::endl;
    std::cout << "    '10' * ''       .. " << ((mul4.compare("0")  == 0)  ? "pass" : fail4) << std::endl;
}

void test_add()
{
    std::cout << std::endl;
    std::cout << " Testing test_add() .. " << std::endl;

    std::string val1 = "10";
    std::string val2 = "200";
    std::string val3 = "0";
    std::string val4 = "";

    std::string add1 = add(val1, val2);
    std::string add2 = add(val2, val1);
    std::string add3 = add(val3, val1);
    std::string add4 = add(val4, val1);

    std::string fail1 = "fail (" + add1 + ")";
    std::string fail2 = "fail (" + add2 + ")";
    std::string fail3 = "fail (" + add3 + ")";
    std::string fail4 = "fail (" + add4 + ")";

    std::cout << "    '10' + '200'    .. " << ((add1.compare("210") == 0) ? "pass" : fail1) << std::endl;
    std::cout << "    '200' + '10'    .. " << ((add2.compare("210") == 0) ? "pass" : fail2) << std::endl;
    std::cout << "    '0' + '10'      .. " << ((add3.compare("10") == 0)  ? "pass" : fail3) << std::endl;
    std::cout << "    '' + '10'       .. " << ((add4.compare("10") == 0)  ? "pass" : fail4) << std::endl;
}
