# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MyCustomMessage(type):
    """Metaclass of message 'MyCustomMessage'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('ros2_bridge_support_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ros2_bridge_support_pkg.msg.MyCustomMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__my_custom_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__my_custom_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__my_custom_message
            cls._TYPE_SUPPORT = module.type_support_msg__msg__my_custom_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__my_custom_message

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MyCustomMessage(metaclass=Metaclass_MyCustomMessage):
    """Message class 'MyCustomMessage'."""

    __slots__ = [
        '_value_boolean',
        '_value_integer',
        '_value_float',
        '_value_string',
    ]

    _fields_and_field_types = {
        'value_boolean': 'boolean',
        'value_integer': 'int32',
        'value_float': 'float',
        'value_string': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.value_boolean = kwargs.get('value_boolean', bool())
        self.value_integer = kwargs.get('value_integer', int())
        self.value_float = kwargs.get('value_float', float())
        self.value_string = kwargs.get('value_string', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.value_boolean != other.value_boolean:
            return False
        if self.value_integer != other.value_integer:
            return False
        if self.value_float != other.value_float:
            return False
        if self.value_string != other.value_string:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def value_boolean(self):
        """Message field 'value_boolean'."""
        return self._value_boolean

    @value_boolean.setter
    def value_boolean(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'value_boolean' field must be of type 'bool'"
        self._value_boolean = value

    @property
    def value_integer(self):
        """Message field 'value_integer'."""
        return self._value_integer

    @value_integer.setter
    def value_integer(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'value_integer' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'value_integer' field must be an integer in [-2147483648, 2147483647]"
        self._value_integer = value

    @property
    def value_float(self):
        """Message field 'value_float'."""
        return self._value_float

    @value_float.setter
    def value_float(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'value_float' field must be of type 'float'"
        self._value_float = value

    @property
    def value_string(self):
        """Message field 'value_string'."""
        return self._value_string

    @value_string.setter
    def value_string(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'value_string' field must be of type 'str'"
        self._value_string = value
