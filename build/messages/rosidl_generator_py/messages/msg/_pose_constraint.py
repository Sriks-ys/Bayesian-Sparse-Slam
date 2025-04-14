# generated from rosidl_generator_py/resource/_idl.py.em
# with input from messages:msg/PoseConstraint.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'covariance'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PoseConstraint(type):
    """Metaclass of message 'PoseConstraint'."""

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
                'messages.msg.PoseConstraint')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__pose_constraint
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__pose_constraint
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__pose_constraint
            cls._TYPE_SUPPORT = module.type_support_msg__msg__pose_constraint
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__pose_constraint

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PoseConstraint(metaclass=Metaclass_PoseConstraint):
    """Message class 'PoseConstraint'."""

    __slots__ = [
        '_pose1_id',
        '_pose2_id',
        '_dx',
        '_dy',
        '_dtheta',
        '_covariance',
    ]

    _fields_and_field_types = {
        'pose1_id': 'int32',
        'pose2_id': 'int32',
        'dx': 'float',
        'dy': 'float',
        'dtheta': 'float',
        'covariance': 'float[9]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 9),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.pose1_id = kwargs.get('pose1_id', int())
        self.pose2_id = kwargs.get('pose2_id', int())
        self.dx = kwargs.get('dx', float())
        self.dy = kwargs.get('dy', float())
        self.dtheta = kwargs.get('dtheta', float())
        if 'covariance' not in kwargs:
            self.covariance = numpy.zeros(9, dtype=numpy.float32)
        else:
            self.covariance = numpy.array(kwargs.get('covariance'), dtype=numpy.float32)
            assert self.covariance.shape == (9, )

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
        if self.pose1_id != other.pose1_id:
            return False
        if self.pose2_id != other.pose2_id:
            return False
        if self.dx != other.dx:
            return False
        if self.dy != other.dy:
            return False
        if self.dtheta != other.dtheta:
            return False
        if all(self.covariance != other.covariance):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def pose1_id(self):
        """Message field 'pose1_id'."""
        return self._pose1_id

    @pose1_id.setter
    def pose1_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'pose1_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'pose1_id' field must be an integer in [-2147483648, 2147483647]"
        self._pose1_id = value

    @builtins.property
    def pose2_id(self):
        """Message field 'pose2_id'."""
        return self._pose2_id

    @pose2_id.setter
    def pose2_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'pose2_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'pose2_id' field must be an integer in [-2147483648, 2147483647]"
        self._pose2_id = value

    @builtins.property
    def dx(self):
        """Message field 'dx'."""
        return self._dx

    @dx.setter
    def dx(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'dx' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'dx' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._dx = value

    @builtins.property
    def dy(self):
        """Message field 'dy'."""
        return self._dy

    @dy.setter
    def dy(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'dy' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'dy' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._dy = value

    @builtins.property
    def dtheta(self):
        """Message field 'dtheta'."""
        return self._dtheta

    @dtheta.setter
    def dtheta(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'dtheta' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'dtheta' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._dtheta = value

    @builtins.property
    def covariance(self):
        """Message field 'covariance'."""
        return self._covariance

    @covariance.setter
    def covariance(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'covariance' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 9, \
                "The 'covariance' numpy.ndarray() must have a size of 9"
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
                 len(value) == 9 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'covariance' field must be a set or sequence with length 9 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._covariance = numpy.array(value, dtype=numpy.float32)
