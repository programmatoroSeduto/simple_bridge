
(cl:in-package :asdf)

(defsystem "ros1_bridge_support_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "MyCustomMessage" :depends-on ("_package_MyCustomMessage"))
    (:file "_package_MyCustomMessage" :depends-on ("_package"))
  ))