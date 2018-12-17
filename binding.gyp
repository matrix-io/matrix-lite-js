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
      "sources": ["<!@(node -p \"require('fs').readdirSync('./hal_wrapper').map(f=>'hal_wrapper/'+f).join(' ')\")", 
                  "<!@(node -p \"require('fs').readdirSync('./hal_wrapper/drivers').map(f=>'hal_wrapper/drivers/'+f).join(' ')\")"]
    }
  ]
}