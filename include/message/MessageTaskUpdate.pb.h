// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageTaskUpdate.proto

#ifndef PROTOBUF_MessageTaskUpdate_2eproto__INCLUDED
#define PROTOBUF_MessageTaskUpdate_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_MessageTaskUpdate_2eproto();
void protobuf_AssignDesc_MessageTaskUpdate_2eproto();
void protobuf_ShutdownFile_MessageTaskUpdate_2eproto();

class MessageTaskUpdate;

// ===================================================================

class MessageTaskUpdate : public ::google::protobuf::Message {
 public:
  MessageTaskUpdate();
  virtual ~MessageTaskUpdate();

  MessageTaskUpdate(const MessageTaskUpdate& from);

  inline MessageTaskUpdate& operator=(const MessageTaskUpdate& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageTaskUpdate& default_instance();

  void Swap(MessageTaskUpdate* other);

  // implements Message ----------------------------------------------

  MessageTaskUpdate* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MessageTaskUpdate& from);
  void MergeFrom(const MessageTaskUpdate& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 status = 1;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 1;
  inline ::google::protobuf::int32 status() const;
  inline void set_status(::google::protobuf::int32 value);

  // repeated string output = 2;
  inline int output_size() const;
  inline void clear_output();
  static const int kOutputFieldNumber = 2;
  inline const ::std::string& output(int index) const;
  inline ::std::string* mutable_output(int index);
  inline void set_output(int index, const ::std::string& value);
  inline void set_output(int index, const char* value);
  inline void set_output(int index, const char* value, size_t size);
  inline ::std::string* add_output();
  inline void add_output(const ::std::string& value);
  inline void add_output(const char* value);
  inline void add_output(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& output() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_output();

  // @@protoc_insertion_point(class_scope:MessageTaskUpdate)
 private:
  inline void set_has_status();
  inline void clear_has_status();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::std::string> output_;
  ::google::protobuf::int32 status_;
  friend void  protobuf_AddDesc_MessageTaskUpdate_2eproto();
  friend void protobuf_AssignDesc_MessageTaskUpdate_2eproto();
  friend void protobuf_ShutdownFile_MessageTaskUpdate_2eproto();

  void InitAsDefaultInstance();
  static MessageTaskUpdate* default_instance_;
};
// ===================================================================


// ===================================================================

// MessageTaskUpdate

// required int32 status = 1;
inline bool MessageTaskUpdate::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageTaskUpdate::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageTaskUpdate::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageTaskUpdate::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::google::protobuf::int32 MessageTaskUpdate::status() const {
  // @@protoc_insertion_point(field_get:MessageTaskUpdate.status)
  return status_;
}
inline void MessageTaskUpdate::set_status(::google::protobuf::int32 value) {
  set_has_status();
  status_ = value;
  // @@protoc_insertion_point(field_set:MessageTaskUpdate.status)
}

// repeated string output = 2;
inline int MessageTaskUpdate::output_size() const {
  return output_.size();
}
inline void MessageTaskUpdate::clear_output() {
  output_.Clear();
}
inline const ::std::string& MessageTaskUpdate::output(int index) const {
  // @@protoc_insertion_point(field_get:MessageTaskUpdate.output)
  return output_.Get(index);
}
inline ::std::string* MessageTaskUpdate::mutable_output(int index) {
  // @@protoc_insertion_point(field_mutable:MessageTaskUpdate.output)
  return output_.Mutable(index);
}
inline void MessageTaskUpdate::set_output(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:MessageTaskUpdate.output)
  output_.Mutable(index)->assign(value);
}
inline void MessageTaskUpdate::set_output(int index, const char* value) {
  output_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskUpdate.output)
}
inline void MessageTaskUpdate::set_output(int index, const char* value, size_t size) {
  output_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskUpdate.output)
}
inline ::std::string* MessageTaskUpdate::add_output() {
  return output_.Add();
}
inline void MessageTaskUpdate::add_output(const ::std::string& value) {
  output_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:MessageTaskUpdate.output)
}
inline void MessageTaskUpdate::add_output(const char* value) {
  output_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:MessageTaskUpdate.output)
}
inline void MessageTaskUpdate::add_output(const char* value, size_t size) {
  output_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:MessageTaskUpdate.output)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
MessageTaskUpdate::output() const {
  // @@protoc_insertion_point(field_list:MessageTaskUpdate.output)
  return output_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
MessageTaskUpdate::mutable_output() {
  // @@protoc_insertion_point(field_mutable_list:MessageTaskUpdate.output)
  return &output_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageTaskUpdate_2eproto__INCLUDED
