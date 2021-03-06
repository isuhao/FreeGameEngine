﻿#ifndef H__TEXTURE_H
#define H__TEXTURE_H

#include "render_state.h"
#include "render_resource.h"

namespace ora
{

    typedef SmartPtr<class Texture> TexturePtr;

    class Texture : public IResource
    {
    public:
        Texture();
        virtual ~Texture();

        virtual bool load(const std::string & filename);
        virtual bool save(const std::string & filename);

        void loadingImmediately();

        bool create(uint32 levels, uint32 width, uint32 height, TextureFormat format, const void* pPixelData, size_t size);
        bool create(GLuint handle, uint32 width, uint32 height, TextureFormat format);

        void setUWrap(TextureWrap wrap);
        TextureWrap getUWrap() const{ return uwrap_; }

        void setVWrap(TextureWrap wrap);
        TextureWrap getVWrap() const { return vwrap_; }

        void setQuality(TextureQuality quality);
        TextureQuality getQuality() const { return quality_; }

        const std::string & getResource() const {  return resource_; }
        TextureFormat getFormat() const { return format_; }
        uint32 getWidth() const { return width_; }
        uint32 getHeight() const { return height_; }
        bool   isMipmapped() const { return mipmapped_ != 0; }
        GLuint getHandle() const { return handle_; }

        bool bind();
        // 强制将当前GL纹理设置为0
        void unbind();
        // 如果当前GL纹理是自己，将其设置为0，并返回true。否则返回false。
        // 当纹理对象析构的时候，可能需要此函数。
        bool tryUnbind();

    protected:
        
        virtual void doLoading();
        void destroy();

        virtual void updateParameter();

    protected:
        virtual void generateMipmaps();
        void onDeviceClose();

        std::string         resource_;
        TextureFormat       format_;
        GLuint              handle_;
        uint32              width_;
        uint32              height_;
        int32               mipmapped_;
        int32               parameterDirty_;
        TextureWrap         uwrap_;
        TextureWrap         vwrap_;
        TextureTarget       target_;
        TextureQuality      quality_;

        
        struct TextureLoadingInfo
        {
            uint32  levels;
            char*   pPixelData;
            size_t  size;
        };
        struct TextureLoadingInfo * pLoadingInfo_;
    };


    const int MAX_TEXTURE_STAGE = 8;

    class TextureStage
    {
    public:
        TextureStage();
        ~TextureStage();

        void setUWrap(TextureWrap wrap) { uWrap_ = wrap; }
        TextureWrap getUWrap() const  { return uWrap_; }

        void setVWrap(TextureWrap wrap) {  vWrap_ = wrap; }
        TextureWrap getVWrap() const { return vWrap_; }

        TexturePtr getTexture() { return texture_; }
        void setTexture(TexturePtr tex) {  texture_ = tex; }

        void applyParam();

    private:

        TextureWrap uWrap_;
        TextureWrap vWrap_;
        TexturePtr  texture_;
    };

} // end namespace ora

#endif //H__TEXTURE_H