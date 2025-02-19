// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: format.proto
// Protobuf C++ Version: 6.31.0-dev

#include "format.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace pkg {

inline constexpr Payload::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        key_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        value_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()) {}

template <typename>
PROTOBUF_CONSTEXPR Payload::Payload(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(Payload_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct PayloadDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PayloadDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~PayloadDefaultTypeInternal() {}
  union {
    Payload _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PayloadDefaultTypeInternal _Payload_default_instance_;
}  // namespace pkg
static constexpr const ::_pb::EnumDescriptor *PROTOBUF_NONNULL *PROTOBUF_NULLABLE
    file_level_enum_descriptors_format_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor *PROTOBUF_NONNULL *PROTOBUF_NULLABLE
    file_level_service_descriptors_format_2eproto = nullptr;
const ::uint32_t
    TableStruct_format_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        PROTOBUF_FIELD_OFFSET(::pkg::Payload, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::pkg::Payload, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::pkg::Payload, _impl_.key_),
        PROTOBUF_FIELD_OFFSET(::pkg::Payload, _impl_.value_),
        0,
        1,
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, 10, -1, sizeof(::pkg::Payload)},
};
static const ::_pb::Message* PROTOBUF_NONNULL const file_default_instances[] = {
    &::pkg::_Payload_default_instance_._instance,
};
const char descriptor_table_protodef_format_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\014format.proto\022\003pkg\"%\n\007Payload\022\013\n\003key\030\001 "
    "\001(\t\022\r\n\005value\030\002 \001(\t"
};
static ::absl::once_flag descriptor_table_format_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_format_2eproto = {
    false,
    false,
    58,
    descriptor_table_protodef_format_2eproto,
    "format.proto",
    &descriptor_table_format_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_format_2eproto::offsets,
    file_level_enum_descriptors_format_2eproto,
    file_level_service_descriptors_format_2eproto,
};
namespace pkg {
// ===================================================================

class Payload::_Internal {
 public:
  using HasBits =
      decltype(std::declval<Payload>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
      8 * PROTOBUF_FIELD_OFFSET(Payload, _impl_._has_bits_);
};

Payload::Payload(::google::protobuf::Arena* PROTOBUF_NULLABLE arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, Payload_class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:pkg.Payload)
}
PROTOBUF_NDEBUG_INLINE Payload::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena, const Impl_& from,
    const ::pkg::Payload& from_msg)
      : _has_bits_{from._has_bits_},
        _cached_size_{0},
        key_(arena, from.key_),
        value_(arena, from.value_) {}

Payload::Payload(
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena,
    const Payload& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, Payload_class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  Payload* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);

  // @@protoc_insertion_point(copy_constructor:pkg.Payload)
}
PROTOBUF_NDEBUG_INLINE Payload::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena)
      : _cached_size_{0},
        key_(arena),
        value_(arena) {}

inline void Payload::SharedCtor(::_pb::Arena* PROTOBUF_NULLABLE arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
Payload::~Payload() {
  // @@protoc_insertion_point(destructor:pkg.Payload)
  SharedDtor(*this);
}
inline void Payload::SharedDtor(MessageLite& self) {
  Payload& this_ = static_cast<Payload&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_.key_.Destroy();
  this_._impl_.value_.Destroy();
  this_._impl_.~Impl_();
}

inline void* PROTOBUF_NONNULL Payload::PlacementNew_(
    const void* PROTOBUF_NONNULL, void* PROTOBUF_NONNULL mem,
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena) {
  return ::new (mem) Payload(arena);
}
constexpr auto Payload::InternalNewImpl_() {
  return ::google::protobuf::internal::MessageCreator::CopyInit(sizeof(Payload),
                                            alignof(Payload));
}
constexpr auto Payload::InternalGenerateClassData_() {
  return ::google::protobuf::internal::ClassDataFull{
      ::google::protobuf::internal::ClassData{
          &_Payload_default_instance_._instance,
          &_table_.header,
          nullptr,  // OnDemandRegisterArenaDtor
          nullptr,  // IsInitialized
          &Payload::MergeImpl,
          ::google::protobuf::Message::GetNewImpl<Payload>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
          &Payload::SharedDtor,
          ::google::protobuf::Message::GetClearImpl<Payload>(), &Payload::ByteSizeLong,
              &Payload::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
          PROTOBUF_FIELD_OFFSET(Payload, _impl_._cached_size_),
          false,
      },
      &Payload::kDescriptorMethods,
      &descriptor_table_format_2eproto,
      nullptr,  // tracker
  };
}

PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 const ::google::protobuf::internal::ClassDataFull
        Payload_class_data_ =
            Payload::InternalGenerateClassData_();

const ::google::protobuf::internal::ClassData* PROTOBUF_NONNULL Payload::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&Payload_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(Payload_class_data_.tc_table);
  return Payload_class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 28, 2>
Payload::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(Payload, _impl_._has_bits_),
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    Payload_class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::pkg::Payload>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // optional string value = 2;
    {::_pbi::TcParser::FastSS1,
     {18, 1, 0, PROTOBUF_FIELD_OFFSET(Payload, _impl_.value_)}},
    // optional string key = 1;
    {::_pbi::TcParser::FastSS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(Payload, _impl_.key_)}},
  }}, {{
    65535, 65535
  }}, {{
    // optional string key = 1;
    {PROTOBUF_FIELD_OFFSET(Payload, _impl_.key_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kRawString | ::_fl::kRepAString)},
    // optional string value = 2;
    {PROTOBUF_FIELD_OFFSET(Payload, _impl_.value_), _Internal::kHasBitsOffset + 1, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kRawString | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\13\3\5\0\0\0\0\0"
    "pkg.Payload"
    "key"
    "value"
  }},
};
PROTOBUF_NOINLINE void Payload::Clear() {
// @@protoc_insertion_point(message_clear_start:pkg.Payload)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if ((cached_has_bits & 0x00000003u) != 0) {
    if ((cached_has_bits & 0x00000001u) != 0) {
      _impl_.key_.ClearNonDefaultToEmpty();
    }
    if ((cached_has_bits & 0x00000002u) != 0) {
      _impl_.value_.ClearNonDefaultToEmpty();
    }
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
::uint8_t* PROTOBUF_NONNULL Payload::_InternalSerialize(
    const ::google::protobuf::MessageLite& base, ::uint8_t* PROTOBUF_NONNULL target,
    ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) {
  const Payload& this_ = static_cast<const Payload&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
::uint8_t* PROTOBUF_NONNULL Payload::_InternalSerialize(
    ::uint8_t* PROTOBUF_NONNULL target,
    ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) const {
  const Payload& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
  // @@protoc_insertion_point(serialize_to_array_start:pkg.Payload)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = this_._impl_._has_bits_[0];
  // optional string key = 1;
  if ((cached_has_bits & 0x00000001u) != 0) {
    const std::string& _s = this_._internal_key();
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(_s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormat::SERIALIZE,
                                "pkg.Payload.key");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // optional string value = 2;
  if ((cached_has_bits & 0x00000002u) != 0) {
    const std::string& _s = this_._internal_value();
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(_s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormat::SERIALIZE,
                                "pkg.Payload.value");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  if (ABSL_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pkg.Payload)
  return target;
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
::size_t Payload::ByteSizeLong(const MessageLite& base) {
  const Payload& this_ = static_cast<const Payload&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
::size_t Payload::ByteSizeLong() const {
  const Payload& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
  // @@protoc_insertion_point(message_byte_size_start:pkg.Payload)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  ::_pbi::Prefetch5LinesFrom7Lines(&this_);
  cached_has_bits = this_._impl_._has_bits_[0];
  if ((cached_has_bits & 0x00000003u) != 0) {
    // optional string key = 1;
    if ((cached_has_bits & 0x00000001u) != 0) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                      this_._internal_key());
    }
    // optional string value = 2;
    if ((cached_has_bits & 0x00000002u) != 0) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                      this_._internal_value());
    }
  }
  return this_.MaybeComputeUnknownFieldsSize(total_size,
                                             &this_._impl_._cached_size_);
}

void Payload::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<Payload*>(&to_msg);
  auto& from = static_cast<const Payload&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:pkg.Payload)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if ((cached_has_bits & 0x00000003u) != 0) {
    if ((cached_has_bits & 0x00000001u) != 0) {
      _this->_internal_set_key(from._internal_key());
    }
    if ((cached_has_bits & 0x00000002u) != 0) {
      _this->_internal_set_value(from._internal_value());
    }
  }
  _this->_impl_._has_bits_[0] |= cached_has_bits;
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void Payload::CopyFrom(const Payload& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pkg.Payload)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void Payload::InternalSwap(Payload* PROTOBUF_RESTRICT PROTOBUF_NONNULL other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.key_, &other->_impl_.key_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.value_, &other->_impl_.value_, arena);
}

::google::protobuf::Metadata Payload::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace pkg
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ [[maybe_unused]] =
        (::_pbi::AddDescriptors(&descriptor_table_format_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
