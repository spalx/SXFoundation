/**
 * @file SXNumber.hpp
 * @brief Declaration of the SXNumber class.
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

#ifndef SXNumber_hpp
#define SXNumber_hpp

#include "SXObject.hpp"

namespace spalx {

/**
 * @brief Template class for representing numeric values.
 * @tparam T The type of the numeric value (e.g., int, double).
 */
template <typename T>
class SXNumber : public SXObject
{
public:
    /**
     * @brief Constructor initializing the numeric value.
     * @param value The initial value of the numeric object.
     */
    explicit SXNumber(T value);
    
    /**
     * @brief Create a new number.
     * @return The new number object. nullptr if initialization fails.
     */
    static SXNumber<T>* create(T value);
    
    /**
     * @brief Getter for the numeric value.
     * @return The current value of the numeric object.
     */
    T getValue() const;
    
    /**
     * @brief Setter for the numeric value.
     * @param value The new value to be set for the numeric object.
     */
    void setValue(T value);
    
    /**
     * @brief Compare the numeric value with another object's value.
     * @param pObject The object to compare with.
     * @return Whether values are equal or not.
     */
    virtual bool isEqual(const SXObject* pObject) const override;
    
    /**
     * @brief Create a copy of the numeric object.
     * @return The new copied object.
     */
    virtual SXObject* copy() const override;

private:
    T m_value; /**< The numeric value. */
};

} // namespace spalx

#endif // SXNumber_hpp
