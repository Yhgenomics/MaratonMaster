// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageTaskLogsUpdate.proto

#ifndef PROTOBUF_MessageTaskLogsUpdate_2eproto__INCLUDED
#define PROTOBUF_MessageTaskLogsUpdate_2eproto__INCLUDED

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
void  protobuf_AddDesc_MessageTaskLogsUpdate_2eproto();
void protobuf_AssignDesc_MessageTaskLogsUpdate_2eproto();
void protobuf_ShutdownFile_MessageTaskLogsUpdate_2eproto();

class MessageTaskLogsUpdate;

// ===================================================================

class MessageTaskLogsUpdate : public ::google::protobuf::Message {
 public:
  MessageTaskLogsUpdate();
  virtual ~MessageTaskLogsUpdate();

  MessageTaskLogsUpdate(const MessageTaskLogsUpdate& from);

  inline MessageTaskLogsUpdate& operator=(const MessageTaskLogsUpdate& from) {
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
  static const MessageTaskLogsUpdate& default_instance();

  void Swap(MessageTaskLogsUpdate* other);

  // implements Message ----------------------------------------------

  MessageTaskLogsUpdate* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MessageTaskLogsUpdate& from);
  void MergeFrom(const MessageTaskLogsUpdate& from);
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

  // required int32 errorMark = 1;
  inline bool has_errormark() const;
  inline void clear_errormark();
  static const int kErrorMarkFieldNumber = 1;
  inline ::google::protobuf::int32 errormark() const;
  inline void set_errormark(::google::protobuf::int32 value);

  // required string taskID = 2;
  inline bool has_taskid() const;
  inline void clear_taskid();
  static const int kTaskIDFieldNumber = 2;
  inline const ::std::string& taskid() const;
  inline void set_taskid(const ::std::string& value);
  inline void set_taskid(const char* value);
  inline void set_taskid(const char* value, size_t size);
  inline ::std::string* mutable_taskid();
  inline ::std::string* release_taskid();
  inline void set_allocated_taskid(::std::string* taskid);

  // required string subtaskID = 3;
  inline bool has_subtaskid() const;
  inline void clear_subtaskid();
  static const int kSubtaskIDFieldNumber = 3;
  inline const ::std::string& subtaskid() const;
  inline void set_subtaskid(const ::std::string& value);
  inline void set_subtaskid(const char* value);
  inline void set_subtaskid(const char* value, size_t size);
  inline ::std::string* mutable_subtaskid();
  inline ::std::string* release_subtaskid();
  inline void set_allocated_subtaskid(::std::string* subtaskid);

  // required string servantID = 4;
  inline bool has_servantid() const;
  inline void clear_servantid();
  static const int kServantIDFieldNumber = 4;
  inline const ::std::string& servantid() const;
  inline void set_servantid(const ::std::string& value);
  inline void set_servantid(const char* value);
  inline void set_servantid(const char* value, size_t size);
  inline ::std::string* mutable_servantid();
  inline ::std::string* release_servantid();
  inline void set_allocated_servantid(::std::string* servantid);

  // required string content = 5;
  inline bool has_content() const;
  inline void clear_content();
  static const int kContentFieldNumber = 5;
  inline const ::std::string& content() const;
  inline void set_content(const ::std::string& value);
  inline void set_content(const char* value);
  inline void set_content(const char* value, size_t size);
  inline ::std::string* mutable_content();
  inline ::std::string* release_content();
  inline void set_allocated_content(::std::string* content);

  // @@protoc_insertion_point(class_scope:MessageTaskLogsUpdate)
 private:
  inline void set_has_errormark();
  inline void clear_has_errormark();
  inline void set_has_taskid();
  inline void clear_has_taskid();
  inline void set_has_subtaskid();
  inline void clear_has_subtaskid();
  inline void set_has_servantid();
  inline void clear_has_servantid();
  inline void set_has_content();
  inline void clear_has_content();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* taskid_;
  ::std::string* subtaskid_;
  ::std::string* servantid_;
  ::std::string* content_;
  ::google::protobuf::int32 errormark_;
  friend void  protobuf_AddDesc_MessageTaskLogsUpdate_2eproto();
  friend void protobuf_AssignDesc_MessageTaskLogsUpdate_2eproto();
  friend void protobuf_ShutdownFile_MessageTaskLogsUpdate_2eproto();

  void InitAsDefaultInstance();
  static MessageTaskLogsUpdate* default_instance_;
};
// ===================================================================


// ===================================================================

// MessageTaskLogsUpdate

// required int32 errorMark = 1;
inline bool MessageTaskLogsUpdate::has_errormark() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageTaskLogsUpdate::set_has_errormark() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageTaskLogsUpdate::clear_has_errormark() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageTaskLogsUpdate::clear_errormark() {
  errormark_ = 0;
  clear_has_errormark();
}
inline ::google::protobuf::int32 MessageTaskLogsUpdate::errormark() const {
  // @@protoc_insertion_point(field_get:MessageTaskLogsUpdate.errorMark)
  return errormark_;
}
inline void MessageTaskLogsUpdate::set_errormark(::google::protobuf::int32 value) {
  set_has_errormark();
  errormark_ = value;
  // @@protoc_insertion_point(field_set:MessageTaskLogsUpdate.errorMark)
}

// required string taskID = 2;
inline bool MessageTaskLogsUpdate::has_taskid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageTaskLogsUpdate::set_has_taskid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageTaskLogsUpdate::clear_has_taskid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageTaskLogsUpdate::clear_taskid() {
  if (taskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    taskid_->clear();
  }
  clear_has_taskid();
}
inline const ::std::string& MessageTaskLogsUpdate::taskid() const {
  // @@protoc_insertion_point(field_get:MessageTaskLogsUpdate.taskID)
  return *taskid_;
}
inline void MessageTaskLogsUpdate::set_taskid(const ::std::string& value) {
  set_has_taskid();
  if (taskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    taskid_ = new ::std::string;
  }
  taskid_->assign(value);
  // @@protoc_insertion_point(field_set:MessageTaskLogsUpdate.taskID)
}
inline void MessageTaskLogsUpdate::set_taskid(const char* value) {
  set_has_taskid();
  if (taskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    taskid_ = new ::std::string;
  }
  taskid_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskLogsUpdate.taskID)
}
inline void MessageTaskLogsUpdate::set_taskid(const char* value, size_t size) {
  set_has_taskid();
  if (taskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    taskid_ = new ::std::string;
  }
  taskid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskLogsUpdate.taskID)
}
inline ::std::string* MessageTaskLogsUpdate::mutable_taskid() {
  set_has_taskid();
  if (taskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    taskid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageTaskLogsUpdate.taskID)
  return taskid_;
}
inline ::std::string* MessageTaskLogsUpdate::release_taskid() {
  clear_has_taskid();
  if (taskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = taskid_;
    taskid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageTaskLogsUpdate::set_allocated_taskid(::std::string* taskid) {
  if (taskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete taskid_;
  }
  if (taskid) {
    set_has_taskid();
    taskid_ = taskid;
  } else {
    clear_has_taskid();
    taskid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageTaskLogsUpdate.taskID)
}

// required string subtaskID = 3;
inline bool MessageTaskLogsUpdate::has_subtaskid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MessageTaskLogsUpdate::set_has_subtaskid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MessageTaskLogsUpdate::clear_has_subtaskid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MessageTaskLogsUpdate::clear_subtaskid() {
  if (subtaskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    subtaskid_->clear();
  }
  clear_has_subtaskid();
}
inline const ::std::string& MessageTaskLogsUpdate::subtaskid() const {
  // @@protoc_insertion_point(field_get:MessageTaskLogsUpdate.subtaskID)
  return *subtaskid_;
}
inline void MessageTaskLogsUpdate::set_subtaskid(const ::std::string& value) {
  set_has_subtaskid();
  if (subtaskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    subtaskid_ = new ::std::string;
  }
  subtaskid_->assign(value);
  // @@protoc_insertion_point(field_set:MessageTaskLogsUpdate.subtaskID)
}
inline void MessageTaskLogsUpdate::set_subtaskid(const char* value) {
  set_has_subtaskid();
  if (subtaskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    subtaskid_ = new ::std::string;
  }
  subtaskid_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskLogsUpdate.subtaskID)
}
inline void MessageTaskLogsUpdate::set_subtaskid(const char* value, size_t size) {
  set_has_subtaskid();
  if (subtaskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    subtaskid_ = new ::std::string;
  }
  subtaskid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskLogsUpdate.subtaskID)
}
inline ::std::string* MessageTaskLogsUpdate::mutable_subtaskid() {
  set_has_subtaskid();
  if (subtaskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    subtaskid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageTaskLogsUpdate.subtaskID)
  return subtaskid_;
}
inline ::std::string* MessageTaskLogsUpdate::release_subtaskid() {
  clear_has_subtaskid();
  if (subtaskid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = subtaskid_;
    subtaskid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageTaskLogsUpdate::set_allocated_subtaskid(::std::string* subtaskid) {
  if (subtaskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete subtaskid_;
  }
  if (subtaskid) {
    set_has_subtaskid();
    subtaskid_ = subtaskid;
  } else {
    clear_has_subtaskid();
    subtaskid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageTaskLogsUpdate.subtaskID)
}

// required string servantID = 4;
inline bool MessageTaskLogsUpdate::has_servantid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MessageTaskLogsUpdate::set_has_servantid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MessageTaskLogsUpdate::clear_has_servantid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MessageTaskLogsUpdate::clear_servantid() {
  if (servantid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    servantid_->clear();
  }
  clear_has_servantid();
}
inline const ::std::string& MessageTaskLogsUpdate::servantid() const {
  // @@protoc_insertion_point(field_get:MessageTaskLogsUpdate.servantID)
  return *servantid_;
}
inline void MessageTaskLogsUpdate::set_servantid(const ::std::string& value) {
  set_has_servantid();
  if (servantid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    servantid_ = new ::std::string;
  }
  servantid_->assign(value);
  // @@protoc_insertion_point(field_set:MessageTaskLogsUpdate.servantID)
}
inline void MessageTaskLogsUpdate::set_servantid(const char* value) {
  set_has_servantid();
  if (servantid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    servantid_ = new ::std::string;
  }
  servantid_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskLogsUpdate.servantID)
}
inline void MessageTaskLogsUpdate::set_servantid(const char* value, size_t size) {
  set_has_servantid();
  if (servantid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    servantid_ = new ::std::string;
  }
  servantid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskLogsUpdate.servantID)
}
inline ::std::string* MessageTaskLogsUpdate::mutable_servantid() {
  set_has_servantid();
  if (servantid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    servantid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageTaskLogsUpdate.servantID)
  return servantid_;
}
inline ::std::string* MessageTaskLogsUpdate::release_servantid() {
  clear_has_servantid();
  if (servantid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = servantid_;
    servantid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageTaskLogsUpdate::set_allocated_servantid(::std::string* servantid) {
  if (servantid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete servantid_;
  }
  if (servantid) {
    set_has_servantid();
    servantid_ = servantid;
  } else {
    clear_has_servantid();
    servantid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageTaskLogsUpdate.servantID)
}

// required string content = 5;
inline bool MessageTaskLogsUpdate::has_content() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void MessageTaskLogsUpdate::set_has_content() {
  _has_bits_[0] |= 0x00000010u;
}
inline void MessageTaskLogsUpdate::clear_has_content() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void MessageTaskLogsUpdate::clear_content() {
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_->clear();
  }
  clear_has_content();
}
inline const ::std::string& MessageTaskLogsUpdate::content() const {
  // @@protoc_insertion_point(field_get:MessageTaskLogsUpdate.content)
  return *content_;
}
inline void MessageTaskLogsUpdate::set_content(const ::std::string& value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(value);
  // @@protoc_insertion_point(field_set:MessageTaskLogsUpdate.content)
}
inline void MessageTaskLogsUpdate::set_content(const char* value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskLogsUpdate.content)
}
inline void MessageTaskLogsUpdate::set_content(const char* value, size_t size) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskLogsUpdate.content)
}
inline ::std::string* MessageTaskLogsUpdate::mutable_content() {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageTaskLogsUpdate.content)
  return content_;
}
inline ::std::string* MessageTaskLogsUpdate::release_content() {
  clear_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = content_;
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageTaskLogsUpdate::set_allocated_content(::std::string* content) {
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete content_;
  }
  if (content) {
    set_has_content();
    content_ = content;
  } else {
    clear_has_content();
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageTaskLogsUpdate.content)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageTaskLogsUpdate_2eproto__INCLUDED
