/**
 * @file SXArray.hpp
 * @brief Declaration of the SXArray class.
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

#ifndef SXArray_hpp
#define SXArray_hpp

#include "SXObject.hpp"

namespace spalx {

#define SX_ARRAY_DEFAULT_CAPACITY_INCREMENT 10

/**
 * @class SXArray
 * @brief Ordered collection of objects.
 */
class SXArray : public SXObject
{
public:
    /**
     * @brief Default constructor.
     */
    SXArray();
    
    /**
     * @brief Destructor.
     * @details Before array deletion, removes all objects from the array so their reference count gets decreased by 1.
     */
    ~SXArray();
    
    /**
     * @brief Create a new array with default capacity.
     * @return The new array object. nullptr if initialization fails.
     */
    static SXArray* create();
    
    /**
     * @brief Create a new array with a specific capacity.
     * @param capacity The size of the array to allocate.
     * @return The new array object. nullptr if initialization fails.
     */
    static SXArray* createWithCapacity(unsigned int capacity);
    
    /**
     * @brief Create a new array adding all objects from another array.
     * @details The objects are copied from the other array.
     * @param pOtherArray The array to copy all objects from.
     * @return The new array object. nullptr if initialization fails.
     */
    static SXArray* createWithArray(SXArray* pOtherArray);
    
    /**
     * @brief Create a new array with the contents of a file.
     * @details A new string object is created from each row of the file and then added to the array.
     * @param pFilePath The path of the file to read from.
     * @return The new array object. nullptr if initialization or any file operation fails.
     */
    static SXArray* createWithContentsOfFile(const char* pFilePath);
    
    /**
     * @brief Overloaded subscript operator to access elements by index.
     * @details Provides read-only access to the element at the specified index.
     * @param index The index of the element to access.
     * @return The object at the specified index.
     */
    SXObject* operator[](unsigned int index) const;
    
    /**
     * @brief Initialize the array with default capacity.
     * @details Calling this method is only mandatory when the array is created with the new operator rather than the create methods.
     * @return Whether initialization was successful.
     */
    bool init();
    
    /**
     * @brief Initialize the array with a specific capacity.
     * @details Calling this method is only mandatory when the array is created with the new operator rather than the create methods.
     * @param capacity The size of the array to allocate.
     * @return Whether initialization was successful.
     */
    bool initWithCapacity(unsigned int capacity);
    
    /**
     * @brief Initialize the array adding all objects from another array.
     * @details The objects are copied from the other array. Calling this method is only mandatory when the array is created with the new operator rather than the create methods.
     * @param pOtherArray The array to copy all objects from.
     * @return Whether initialization was successful.
     */
    bool initWithArray(SXArray* pOtherArray);
    
    /**
     * @brief Get the number of elements in the array.
     * @return The number of elements.
     */
    unsigned int count() const;
    
    /**
     * @brief Get the index of a specific object.
     * @param pObject The object to find.
     * @return The index of the object. Returns UINT_MAX if object is not found.
     */
    unsigned int indexOfObject(const SXObject* pObject) const;
    
    /**
     * @brief Get the last object in the array.
     * @return The object.
     */
    SXObject* lastObject() const;
    
    /**
     * @brief Get the object at a specific index.
     * @param index The index of the object to retrieve.
     * @return The object.
     */
    SXObject* objectAtIndex(unsigned int index) const;
    
    /**
     * @brief Check whether the array has a specific object.
     * @param pObject The object to find.
     * @return Whether object exists in the array.
     */
    bool containsObject(SXObject* pObject) const;
    
    /**
     * @brief Add object to the array.
     * @details The reference count of the object is increased by 1.
     * @param pObject The object to add.
     */
    void addObject(SXObject* pObject);
    
    /**
     * @brief Add all objects from another array to the array.
     * @details The reference count of all objects added to the array is increased by 1.
     * @param pOtherArray The array to get all elements from.
     */
    void addObjectsFromArray(SXArray* pOtherArray);
    
    /**
     * @brief Add object to the array, at a specific index.
     * @details The reference count of the object is increased by 1.
     * @param pObject The object to add.
     * @param index The index where the object should be inserted.
     */
    void insertObject(SXObject* pObject, unsigned int index);
    
    /**
     * @brief Remove object from the array.
     * @details The reference count of the object is decreased by 1.
     * @param pObject The object to remove.
     */
    void removeObject(SXObject* pObject);
    
    /**
     * @brief Remove the object from the array at a specific index.
     * @details The reference count of the object is decreased by 1.
     * @param index The index of the object that should be removed.
     */
    void removeObjectAtIndex(unsigned int index);
    
    /**
     * @brief Remove last object from the array.
     * @details The reference count of the object is decreased by 1.
     */
    void removeLastObject();
    
    /**
     * @brief Remove all objects from array, that are contained in another array.
     * @details The reference count of each object is decreased by 1.
     */
    void removeObjectsInArray(SXArray* pOtherArray);
    
    /**
     * @brief Remove all objects from the array.
     * @details The reference count of each object is decreased by 1.
     */
    void removeAllObjects();
    
    /**
     * @brief Compare array with another array.
     * @details All objects at each index of both arrays are compared (by calling isEqual()) against each other.
     * @return Whether the elements of both arrays are equal.
     */
    virtual bool isEqual(const SXObject* pObject) const override;
    
    /**
     * @brief Perform a deep copy of the array.
     * @details Create a new array by copying (copy() is called) each element inside the array.
     * @return The new copied array.
     */
    virtual SXObject* copy() const override;
    
private:
    unsigned int m_capacity{SX_ARRAY_DEFAULT_CAPACITY_INCREMENT}; /**< Capacity of the array. */
    unsigned int m_count{0}; /**< Number of objects in the array. */
    SXObject** m_pArray{nullptr}; /**< A pointer to the array of pointers of the objects in the array. */
    
    /**
     * @brief Resize array to the new capacity.
     * @details This function is called when the capacity is reached and more is needed to allocate new elements.
     * @param capacity The new size of the array.
     */
    void resizeArray(unsigned int capacity);
    
    /**
     * @brief Move all elements one index back starting from the specified index.
     * @details Element at index will be moved to index - 1, and so on, until reaching the end of the array.
     * @param index The index from which the reordering should start.
     */
    void reorderArrayAtIndex(unsigned int index);
};

} // namespace spalx

#endif // SXArray_hpp
