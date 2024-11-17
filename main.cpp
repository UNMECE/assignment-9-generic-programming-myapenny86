#include <iostream>
#include <stdexcept>
#include <limits>

template <typename T>
class GenericArray
{
	private:
		T* data;
		size_t length;

	public:
		GenericArray() : data(nullptr), length(0) {}

		~GenericArray() 
		{
			delete[] data;
		}

		void addElement(T value)
		{
			T* newData = new T[length + 1];
			for(size_t i = 0; i < length; ++i)
			{
				newData[i] = data[i];
			}
			newData[length] = value;
			delete[] data;
			data = newData;
			++length;
		}

		T at(int index) const
		{
			if(index < 0 || static_cast<size_t>(index) >= length)
			{
				throw std::out_of_range("Index out of bounds");
			}
			return data[index];
		}

		size_t size() const
		{
			return length;
		}
		
		T sum() const
		{
			T total = 0;
			for(size_t i = 0; i < length; ++i)
			{
				total += data[i];
			}
			return total;
		}

		T max() const
		{
			if(length == 0)
			{
				throw std::runtime_error("Array is empty");
			}
			T maxValue = std::numeric_limits<T>::lowest();
			for(size_t i = 0; i < length; ++i)
			{
				if(data[i] > maxValue)
				{
					maxValue = data[i];
				}
			}
			return maxValue;
		}

		T min() const
		{
			if(length == 0)
			{
				throw std::runtime_error("Array is empty");
			}
			T minValue = std::numeric_limits<T>::max();
			for(size_t i = 0; i < length; ++i)
			{
				if(data[i] < minValue)
				{
					minValue = data[i];
				}
			}
			return minValue;
		}

		T* slice(int begin, int end) const
		{
			if(begin < 0 || end < 0 || static_cast<size_t>(begin) >= length || static_cast<size_t>(end) >= length || begin > end)
			{
				throw std::out_of_range("Invalid slice bounds");
			}
			size_t newlength = end - begin + 1;
			T* slicedArray = new T[newlength];
			for(size_t i = 0; i < newlength; ++i)
			{
				slicedArray[i] = data[begin + i];
			}
			return slicedArray;
		}
};

int main()
{
	try
	{
		GenericArray<int> int_array;
		int_array.addElement(10);
		int_array.addElement(20);
		int_array.addElement(30);
		int_array.addElement(40);
		int_array.addElement(50);
		
		std::cout << "Size of array is: " << int_array.size() << std::endl;
		std::cout << "Sum of the array is: " << int_array.sum() << std::endl;
		std::cout << "Maximum and minimum of the array are: " << int_array.max() << "\t" << int_array.min() << std::endl;

		int* sliced_array = int_array.slice(1,3);
		std::cout << "Sliced array: ";
		for(int i = 0; i < 3; ++i)
		{
			std::cout << sliced_array[i] << " ";
		}
		std::cout << std::endl;
		
		delete[] sliced_array;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}
