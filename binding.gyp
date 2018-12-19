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
      "sources": ["<!@(node -p \"require('fs').readdirSync('./hal_wrapper').map(f=>'hal_wrapper/'+f).join(' ')\")", 
                  "<!@(node -p \"require('fs').readdirSync('./hal_wrapper/drivers').map(f=>'hal_wrapper/drivers/'+f).join(' ')\")",
                  "<!@(node -p \"require('fs').readdirSync('./hal_wrapper/drivers/sensors').map(f=>'hal_wrapper/drivers/sensors/'+f).join(' ')\")"]
    }
  ]
}