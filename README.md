Misc:
Push the local projects to GitHub
https://gist.github.com/alexpchin/102854243cd066f8b88e

Vulkan SDK installation dir:
C:/VulkanSDK/

May 15th.
https://vulkan-tutorial.com/
https://vulkan-tutorial.com/Overview
https://vulkan-tutorial.com/Development_environment

May 16th
https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Base_code (25 min)

May 22nd:
https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Validation_layers (3 hours + 1.5 hour)
Debug Note: 
1) insall the latest Vulkan SDK to fix the "validation layers requested, but not available!" error.
2) install the latest NVidia driver to fix "VK_EXT_debug_utils" extension not found error.
3) reinstall the latest Vulkan SDK to fix 1) above. Looks like the updating the NVIDIA driver in step 2) somehow modifies the vulkan ExplicitLayers in registry, causing error 1) appear again.