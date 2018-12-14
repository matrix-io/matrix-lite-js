{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],

      "link_settings": {
        "libraries": [
          "-lmatrix_creator_hal"
        ]
      },
      "target_name": "addon",
      "sources": [ "cpp_wrapper/matrix.cpp", "cpp_wrapper/everloop.cpp", "cpp_wrapper/matrix.h" ]
    }
  ]
}