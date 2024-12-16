//
//  YZKTitleTableViewCell.m
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/10/23.
//

#import "YZKTitleTableViewCell.h"

@interface YZKTitleTableViewCell ()

@property (nonatomic, strong) UILabel *titleLabel;

@end

@implementation YZKTitleTableViewCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.font = [UIFont systemFontOfSize:16];
//        titleLabel.textColor = [UIColor blackColor];
        [self.contentView addSubview:titleLabel];
        self.titleLabel = titleLabel;
    }
    return self;
}

- (void)setTitle:(NSString *)title {
    _title = title;
    self.titleLabel.text = title;
    self.titleLabel.frame = CGRectInset(self.contentView.bounds, 20, 0);
}

@end
