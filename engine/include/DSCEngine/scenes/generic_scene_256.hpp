#pragma once

namespace DSC
{
	/*! \brief general-purpose scene with 256KB BG-Main VRAM
		\details Size limits:
		- 256 KB for main backgrounds
		-  64 KB for main objects
		-   8    extended palettes for each main background
		-  16    extended palettes for main objects
		- 128 KB for sub backgrounds
		- 128 KB for sub objects
		-  16    extended palettes for each sub backgrounds
		-  16    extended palettes for sub objects
	 */
	class GenericScene256 : public Scene
	{
	private:
		
	public:
		virtual void init() override;
		virtual void frame() override;
	};
}