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
      # Each index exposes all files inside path
      "sources": ["<!@(ls -1 hal_wrapper/*.cpp)", "<!@(ls -1 hal_wrapper/drivers/*.cpp)", "<!@(ls -1 hal_wrapper/drivers/sensors/*.cpp)"]
    }
  ]
}
