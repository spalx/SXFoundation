/**
 * @file SXDictionary.hpp
 * @brief Declaration of the SXDictionary class.
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

#ifndef SXDictionary_hpp
#define SXDictionary_hpp

#include "SXObject.hpp"
#include "SXArray.hpp"
#include <string>
#include <unordered_map>

namespace spalx {

typedef std::unordered_map<std::string, SXObject*>::iterator SXDictionaryIterator;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Type definition for an iterator over an unordered_map with string keys and SXObject* values.

/**
 * @class SXArray
 * @brief Dynamic collection of key-value pairs.
 */
class SXDictionary : public SXObject
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes the unordered map.
     */
    SXDictionary();
    
    /**
     * @brief Destructor.
     * @details Before map deletion, removes all objects from the map so their reference count gets decreased by 1.
     */
    ~SXDictionary();
    
    /**
     * @brief Create a new dictionary.
     * @return The new dictionary object. nullptr if initialization fails.
     */
    static SXDictionary* create();
    
    /**
     * @brief Overloaded subscript operator to access elements by key.
     * @details Provides read-only access to the element for the specified key.
     * @param rKey The key of the element to access.
     * @return The object for the specified key.
     */
    SXObject* operator[](const std::string& rKey) const;
    
    /**
     * @brief Get the number of elements in the dictionary.
     * @return The number of elements.
     */
    unsigned int count() const;
    
    /**
     * @brief Get all the keys from the dictionary.
     * @return Array of strings (the keys).
     */
    SXArray* allKeys() const;
    
    /**
     * @brief Get the object with the specific key.
     * @param rKey The key of the object to retrieve.
     * @return The object.
     */
    SXObject* objectForKey(const std::string& rKey) const;
    
    /**
     * @brief Add object to the dictionary.
     * @details The reference count of the object is increased by 1.
     * @param pObject The object to add.
     * @param rKey The key to assign to the object.
     */
    void setObject(SXObject* pObject, const std::string& rKey);
    
    /**
     * @brief Remove the object with the specific key.
     * @details The reference count of the object is decreased by 1.
     * @param rKey The key of the object to remove.
     */
    void removeObjectForKey(const std::string& rKey);
    
    /**
     * @brief Remove all objects with the specific keys.
     * @details The reference count of each object is decreased by 1.
     * @param pKeys Array of keys of the objects to remove.
     */
    void removeObjectsForKeys(SXArray* pKeys);
    
    /**
     * @brief Remove all objects.
     * @details The reference count of each object is decreased by 1.
     */
    void removeAllObjects();
    
    /**
     * @brief Get the first element of the map.
     * @return An iterator over the first element of the unordered_map.
     */
    SXDictionaryIterator begin() const;
    
    /**
     * @brief Get the last element of the map.
     * @return An iterator over the last element of the unordered_map. If iterator reaches here, means that there are no more objects in the dictionary.
     */
    SXDictionaryIterator end() const;
    
    /**
     * @brief Perform a deep copy of the dictionary.
     * @details Create a new dictionary by copying (copy() is called) each element inside the dictionary.
     * @return The new copied dictionary.
     */
    virtual SXObject* copy() const override;
    
private:
    std::unordered_map<std::string, SXObject*>* m_pMap; /**< Map container of all objects. */
};

} // namespace spalx

#endif // SXDictionary_hpp
