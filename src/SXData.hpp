/**
 * @file SXData.hpp
 * @brief Declaration of the SXData class.
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

#ifndef SXData_hpp
#define SXData_hpp

#include "SXObject.hpp"
#include "SXString.hpp"
#include <vector>

namespace spalx {

/**
 * @class SXData
 * @brief Wrapper class for byte buffers.
 */
class SXData : public SXObject
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes the bytes vector.
     */
    SXData();
    
    /**
     * @brief Destructor.
     */
    ~SXData();
    
    /**
     * @brief Create a new data object.
     * @return The new data object. nullptr if initialization fails.
     */
    static SXData* create();
    
    /**
     * @brief Create a new data object with the binary contents of a file.
     * @param pFilePath The path of the file to read from.
     * @return The new data object. nullptr if initialization or any file operation fails.
     */
    static SXData* createWithContentsOfFile(const char* pFilePath);
    
    /**
     * @brief Initialize the data object with a specific vector of bytes.
     * @details Calling this method is only mandatory when the object is created with the new operator rather than the create methods.
     * @param rData Reference to the bytes vector.
     * @return Whether initialization was successful.
     */
    bool initWithData(const std::vector<char>& rData);
    
    /**
     * @brief Initialize the data object with the binary contents of a file.
     * @details Calling this method is only mandatory when the object is created with the new operator rather than the create methods.
     * @param pFilePath The path of the file to read from.
     * @return Whether initialization was successful.
     */
    bool initWithContentsOfFile(const char* pFilePath);
    
    /**
     * @brief Number of bytes.
     * @return The size of the vector.
     */
    unsigned long length() const;
    
    /**
     * @brief Write the bytes data to a file.
     * @param pFilePath The path of the file to write to.
     * @return Whether writing was successful.
     */
    bool writeToFile(const char* pFilePath) const;
    
    /**
     * @brief Create a new data object with current object's bytes data.
     * @return The new copied data object.
     */
    virtual SXObject* copy() const override;
    
private:
    std::vector<char>* m_pBytes{nullptr}; /**< Vector of bytes. */
};

} // namespace spalx

#endif // SXData_hpp
