class Contact
  attr_accessor :contactName
  def initial(contactName = "-")
    @contactName
  end

  def to_s
    "Info: " + @contactName
  end
end

class FullContact < Contact
  attr_accessor :contactPhone
  attr_accessor :contactSurname

  def initialize(contactName = "-", contactPhone = "-", contactSurname = "-")
    super(contactName)
    @contactName = contactName
    @contactPhone = contactPhone
    @contactSurname = contactSurname
  end

  def to_s
    "Name: " + contactName + " " + contactSurname + ", phone: " + contactPhone
  end
end

class BlogerContact < FullContact
  attr_accessor :contactBlog

  def initialize(contactName = "-", contactPhone = "-", contactSurname = "-", contactBlog = "no messenger")
    super(contactName, contactPhone, contactSurname)
    @contactBlog = contactBlog
  end

  def to_s
    "Name: " + contactName + " " + contactSurname + ", phone: " + contactPhone + " Blog: " + contactBlog
  end
end

class PhoneBook
  attr_accessor :array

  def initialize(array = "-")
    @array = array
  end

  def add(obj)
    @array.append obj
  end

  def findByName(name)
    @array.select do |i|
      i.contactName.start_with? name
    end
  end

  def sortByName
    @array.sort do |a, b|
      a.contactName > b.name
    end
  end

  def to_s
    array.each do |item|
      puts item
    end
  end
end
