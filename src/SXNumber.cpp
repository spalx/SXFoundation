/**
 * @file SXNumber.hpp
 * @brief Implementation of the SXNumber class.
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

#include "SXNumber.hpp"

namespace spalx {

template <typename T>
SXNumber<T>::SXNumber(T value)
:m_value(value)
{
}

template <typename T>
SXNumber<T>* SXNumber<T>::create(T value)
{
    SXNumber<T>* pNewNumber = new SXNumber(value);
    
    if (pNewNumber) {
        pNewNumber->autorelease();
    }
    
    return pNewNumber;
}

template <typename T>
T SXNumber<T>::getValue() const
{
    return m_value;
}

template <typename T>
void SXNumber<T>::setValue(T value)
{
    m_value = value;
}

template <typename T>
bool SXNumber<T>::isEqual(const SXObject* pObject) const
{
    const SXNumber* pNumber = dynamic_cast<const SXNumber<T>*>(pObject);
    return (pNumber && pNumber->getValue() == m_value);
}

template <typename T>
SXObject* SXNumber<T>::copy() const
{
    return new SXNumber<T>(m_value);
}

template class SXNumber<char>;
template class SXNumber<unsigned char>;
template class SXNumber<short>;
template class SXNumber<unsigned short>;
template class SXNumber<int>;
template class SXNumber<unsigned int>;
template class SXNumber<long>;
template class SXNumber<unsigned long>;
template class SXNumber<long long>;
template class SXNumber<unsigned long long>;
template class SXNumber<float>;
template class SXNumber<double>;
template class SXNumber<bool>;

}
