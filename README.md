# SXFoundation Framework

SXFoundation is a C++ framework heavily influenced by Objective-C's manual memory management principles and the Core Foundation framework. It provides a set of classes and utilities for managing memory, collections, and other fundamental data types.

## Classes

| Name | Description |
| --------- | ------------------------------------------------- |
| SXObject  | Base class from which all other classes are derived. Provides 3 methods for memory management via reference counting mechanism. |
| SXPoolManager  | This is the only class in the framework that does not inherit from SXObject. Its main purpose is to manage the existing autorelease pools in a LIFO principle, so the last pool pushed is always the current pool and it's the pool that gets popped first. |
| SXAutoreleasePool  | Container class for all objects that are marked as autorelease. If the shared SXPoolManager is used, there is no need to make use of this class manually. |
| SXArray  | Ordered collection of objects. |
| SXDictionary  | Dynamic collection of key-value pairs. |
| SXSet  | Unordered collection of distinct objects. |
| SXData | Wrapper class for a byte buffer. |
| SXNumber | Template class for representing numeric values. |
| SXSelector | Simple polymorphic function wrapper. |
| SXNotificationCenter | A notification dispatch mechanism that enables the broadcast of information to registered observers. |

## Usage hints

- Any object instantiated with the new keyword has a reference count of 1, and it's your obligation to delete the object by calling release() or sending it to the autorelease pool by calling autorelease().
- Any object instantiated with any of the create() methods is already in the autorelease pool.
- To make sure that an object passed to your class is always available, increase its reference count by calling retain() and then release it when not needed anymore.
- Do not forget to call SXPoolManager::purgePoolManager() at the end of your program.

### Memory management example

```cpp
// pStr1 has a reference count of 1 and is not in the autorelease pool, so we are the owners of that object and we must release it manually.
SXString* pStr1 = new SXString("Hello,");

// pStr2 has a reference count of 1 but it's in the autorelease pool, so we are not allowed to release it, will be automatically released when the pool is drained.
SXString* pStr2 = SXString::create("World!");

// Prints "Hello, World!" in the console.
SXLog("%s %s", pStr1->getCString(), pStr2->getCString());

// Calling release to free memory used by the string that we created by using new operator.
pStr1->release();

// Delete all pools and call release() on each one of the objects inside them. Calling this method is a must and it should be done only at the end of the program.
SXPoolManager::purgePoolManager();
```

## Autorelease pools
Autorelease pools are used to release memory used by objects marked with the autorelease() method. The first call of that method forces the pool manager to create the first pool and set it as the active pool. But, you can create more pools, with the purpose of narrowing down the scope of the pool from application scope to a concrete block of code scope.

### Creating multiple pools

```cpp
// pStr1 is created in the main pool.
SXString* pStr1 = SXString::create("Hello,");

// We create a new pool and push it to the top of the stack, so starting from here, this is the active pool.
SXPoolManager::sharedPoolManager()->push();

// pStr2 goes to the second (active) pool.
SXString* pStr2 = SXString::create("World!");

// Pop the active (second) pool. pStr2 will be released after this call.
SXPoolManager::sharedPoolManager()->pop();

// pStr1 will only be released when purgePoolManager() is called, since it was created in the first pool (which was created by the pool manager).
SXPoolManager::purgePoolManager();
```

## Arrays, sets and dictionaries
- Use SXArray when you need to store objects in an ordered fashion, and later access them by index.
- Use SXSet when order is not important and you just need a collection of objects which you can iterate over.
- Use SXDictionary when you want to assign a unique string key to each object.

### Example

```cpp
SXString* pStr = SXString::create("Hello, World!");
SXObject* pTmp;

SXArray* pArr = SXArray::create(); // Create an array.
pArr->addObject(pStr); // Add string object to the array.
pTmp = (*pArr)[0]; // Get object from array.

SXSet* pSet = SXSet::create(); // Create a set.
pSet->addObject(pStr); // Add string object to the set.
pTmp = pSet->anyObject(); // Get object from set.

SXDictionary* pDict = SXDictionary::create(); // Create a dictionary.
pDict->setObject(pStr, "someKey"); // Add string object to the dictionary.
pTmp = (*pDict)["someKey"]; // Get object from dictionary.
```

## Strings, numbers and bytes
- SXString is a wrapper class for strings.
- SXNumber is a template class for representing numeric values.
- SXData is a wrapper class for byte buffers.

### Example

```cpp
SXString* pStr = SXString::create("Hello, World!"); // Create a string.
const char* pCStr = pStr->getCString(); // Get C-style string value.

SXNumber<int>* pNum = SXNumber<int>::create(10); // Create a number.
int num = pNum->getValue(); // Get numeric value.

SXData* pData = SXData::createWithContentsOfFile("file1.jpg"); // Create a data object from the contents of a file.
if (pData) {
    pData->writeToFile("file2.jpg"); // Write the bytes to another file.
}
```

## Selectors
SXSelector is a simple polymorphic function wrapper. Since it's subclassing SXObject, it can be easily added to arrays, sets and dictionaries whenever needed. In that way, for example, you can have an array of callbacks.

### Examples
```cpp
// In all the examples below, the function is receiving one SXDictionary* as argument and returning void. But that's just an example, you can modify both the arguments and the return type.

// Creating a selector using lambda notation.
SXSelector<void(SXDictionary*)>* pSelector1 = new SXSelector<void(SXDictionary*)>([](SXDictionary* dict) {
    myCallback(dict);
});

// Creating a seletor by just passing the reference of the function.
SXSelector<void(SXDictionary*)>* pSelector2 = new SXSelector<void(SXDictionary*)>(&myCallback);

// Creating a selector by binding an object's method
MyClass* pObj = new MyClass();
SXSelector<void(SXDictionary*)>* pSelector3 = new SXSelector<void(SXDictionary*)>(std::bind(&MyClass::myCallback, pObj, std::placeholders::_1));
```

## The notification center
The SXNotificationCenter class is a singleton class that allows sending notifications to observers. Any SXObject subclass can be registered as an observer.

### Example
```cpp
SXNotificationCenter* pNotificationCenter = SXNotificationCenter::defaultCenter();

// Create the seletor which will be called when the notification is received.
SXSelector<void(SXDictionary*)>* pSelector = new SXSelector<void(SXDictionary*)>(&myCallback);

// Register the selector for notifications named "notification_name"
pNotificationCenter->addObserver(pSelector, "notification_name");

// (Optional) Create a dictionary to pass to the callback as extra information.
SXDictionary* pInfo = SXDictionary::create();

// Post a notification called "notification_name" (will trigger the selector registered as observer).
pNotificationCenter->postNotification("notification_name", pInfo);
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
