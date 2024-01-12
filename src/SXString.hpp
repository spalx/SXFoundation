/**
 * @file SXString.hpp
 * @brief Declaration of the SXString class.
 *
 * @copyright (c) 2024 Artavazd Barseghyan
 * @details This software is released under the MIT License.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SXString_hpp
#define SXString_hpp

#include "SXObject.hpp"
#include <string>

namespace spalx {

/**
 * @class SXString
 * @brief Wrapper class for strings.
 */
class SXString : public SXObject
{
public:
    /**
     * @brief Default constructor.
     * @details Creates an empty string.
     */
    SXString();
    
    /**
     * @brief Parameterized constructor.
     * @details Create from C string.
     */
    SXString(const char* pString);
    
    /**
     * @brief Copy constructor.
     * @details Get string value from another SXString object.
     */
    SXString(const SXString& rString);
    
    /**
     * @brief Destructor.
     */
    ~SXString();
    
    /**
     * @brief Create a new string from the provided C string.
     * @return The new string object. nullptr if initialization fails.
     */
    static SXString* create(const char* pString);
    
    /**
     * @brief Create a new string with the contents of a file.
     * @param pFilePath The path of the file to read from.
     * @return The new string object. nullptr if initialization or any file operation fails.
     */
    static SXString* createWithContentsOfFile(const char* pFilePath);
    
    /**
     * @brief Assignment operator overload.
     * @param rOtherString The string to be assigned.
     * @return Reference to the string assigned.
     */
    SXString& operator=(const SXString& rOtherString);
    
    /**
     * @brief Overloaded subscript operator to access chars by index.
     * @details Provides read-only access to the character at the specified index.
     * @param index The index of the char to access.
     * @return The char at the specified index.
     */
    char operator[](unsigned int index) const;
    
    /**
     * @brief Change the string value.
     * @param pString The C string to set.
     */
    void setValue(const char* pString);
    
    /**
     * @brief Convert string to int and get it.
     * @return The integer value.
     */
    int intValue() const;
    
    /**
     * @brief Convert string to unsigned long and get it.
     * @return The unsigned long value.
     */
    unsigned long ulValue() const;
    
    /**
     * @brief Convert string to float and get it.
     * @return The float value.
     */
    float floatValue() const;
    
    /**
     * @brief Convert string to doule and get it.
     * @return The double value.
     */
    double doubleValue() const;
    
    /**
     * @brief Convert string to bool and get it.
     * @return The boolean value.
     */
    bool boolValue() const;
    
    /**
     * @brief Get the C-style string value.
     * @return The C string.
     */
    const char* getCString() const;
    
    /**
     * @brief Get length of the string.
     * @return The length.
     */
    unsigned long length() const;
    
    /**
     * @brief Compare string value with a C string.
     * @return 0 if strings are equal, >0 if the first non-matching character in the string is greater (in ASCII) than that of pString, <0 if the first non-matching character in the string is lower (in ASCII) than that of pString.
     */
    int compare(const char* pString) const;
    
    /**
     * @brief Compare string with another string.
     * @details Actually their C style string values are compared.
     * @return Whether the strings are equal or not.
     */
    virtual bool isEqual(const SXObject* pObject) const override;
    
    /**
     * @brief Create a new string with current string's value.
     * @return The new copied string.
     */
    virtual SXObject* copy() const override;
    
private:
    std::string m_string; /**< C-style container string. */
};

} // namespace spalx

#endif // SXString_hpp
