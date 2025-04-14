# generated from rosidl_generator_py/resource/_idl.py.em
# with input from messages:msg/LandmarkConstraint.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'covariance'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LandmarkConstraint(type):
    """Metaclass of message 'LandmarkConstraint'."""

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
            module = import_type_support('messages')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'messages.msg.LandmarkConstraint')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__landmark_constraint
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__landmark_constraint
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__landmark_constraint
            cls._TYPE_SUPPORT = module.type_support_msg__msg__landmark_constraint
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__landmark_constraint

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class LandmarkConstraint(metaclass=Metaclass_LandmarkConstraint):
    """Message class 'LandmarkConstraint'."""

    __slots__ = [
        '_header',
        '_pose_id',
        '_landmark_id',
        '_rho',
        '_alpha',
        '_covariance',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'pose_id': 'int32',
        'landmark_id': 'int32',
        'rho': 'float',
        'alpha': 'float',
        'covariance': 'float[4]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 4),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.pose_id = kwargs.get('pose_id', int())
        self.landmark_id = kwargs.get('landmark_id', int())
        self.rho = kwargs.get('rho', float())
        self.alpha = kwargs.get('alpha', float())
        if 'covariance' not in kwargs:
            self.covariance = numpy.zeros(4, dtype=numpy.float32)
        else:
            self.covariance = numpy.array(kwargs.get('covariance'), dtype=numpy.float32)
            assert self.covariance.shape == (4, )

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
        if self.header != other.header:
            return False
        if self.pose_id != other.pose_id:
            return False
        if self.landmark_id != other.landmark_id:
            return False
        if self.rho != other.rho:
            return False
        if self.alpha != other.alpha:
            return False
        if all(self.covariance != other.covariance):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def pose_id(self):
        """Message field 'pose_id'."""
        return self._pose_id

    @pose_id.setter
    def pose_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'pose_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'pose_id' field must be an integer in [-2147483648, 2147483647]"
        self._pose_id = value

    @builtins.property
    def landmark_id(self):
        """Message field 'landmark_id'."""
        return self._landmark_id

    @landmark_id.setter
    def landmark_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'landmark_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'landmark_id' field must be an integer in [-2147483648, 2147483647]"
        self._landmark_id = value

    @builtins.property
    def rho(self):
        """Message field 'rho'."""
        return self._rho

    @rho.setter
    def rho(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rho' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'rho' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._rho = value

    @builtins.property
    def alpha(self):
        """Message field 'alpha'."""
        return self._alpha

    @alpha.setter
    def alpha(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'alpha' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'alpha' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._alpha = value

    @builtins.property
    def covariance(self):
        """Message field 'covariance'."""
        return self._covariance

    @covariance.setter
    def covariance(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'covariance' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 4, \
                "The 'covariance' numpy.ndarray() must have a size of 4"
            self._covariance = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'covariance' field must be a set or sequence with length 4 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._covariance = numpy.array(value, dtype=numpy.float32)
